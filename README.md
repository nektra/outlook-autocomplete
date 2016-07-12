# outlook-autocomplete
A demo addin to customize the autocomplete stream on-the-fly, for Outlook 2007 (x86).

IMPORTANT
---------
The version we've been working on is Outlook 2007, x86 edition, version 12.0.6744.5000. 
You should at least consider using 12.0 as newer versions may include changes on the 
internal file and/or code organization. However, our approach should be portable, with
proper changes, to newer versions of Outlook.

Requirements
============
To build and run this sample, you need:

- Visual Studio compiler. Included project is for VS2012.
- Outlook 12.0/x86 (preferably 6744 build)

How Autocomplete works in Outlook
=================================
The list of addresses that you see when autocompletion triggers in any "address" type 
field, such as "To:", "Cc:", "Bcc:", etc, is stored in a NK2 file under 
`%USERPROFILE%\AppData\Roaming\Microsoft\Outlook ` where cache entries are stored.

Outlook reads the file at request, e.g: when the user is going to compose a new mail
message. After the user sends the message, Outlook will re-write the file with the 
"Record Weight" field changed. Weights are modified, and file reordered by this field,
according to the frequency or popularity of each address. 

Many tools exist to modify the file "offline", such as NK2Edit. Our purpose is to
change the name cache on-the-fly, seeing the changes in realtime. 

Internal structure
==================
The NK2 file structure is known and documented by Microsoft itself [1]. The on memory
version follows the same general structure: a metadata header, followed by the database
rowset. The structures to hold the rows and rowset are publicly documented in MSDN [2][3].

From our research, Outlook does not enforce any particular ordering in the file. Basically,
it will show the entries according to the order in the file. Our project includes code for 
sorting by weight criteria or swapping rows to alter the order; both can be triggered with
the provided UI.

Our approach
============
How we got the pointer to the in-memory rowsets to be able to modify them online?

This is the flow of Outlook when reading the NK2 autocomplete cache file, in pseudocode:
```
handle = GlobalAlloc();
buf = GlobalLock(handle);
ReadFile(buf);
GlobalUnlock(buf);
stream = CreateStreamOnHGLOBAL(buf);
/* Read 12-byte header */
stream.Read_DWORD();					/* Read and verifies  Nk2 header 0xBAADF00D */
stream.Read_DWORD();					/* Read and verifies 0x0000000A (major version) */
stream.Read_DWORD();					/* Read and verifies 0 (minor version) */
stream.Read_row_count();				/* Read number of rows */
stream.Read_all_rows();					
/* read extra information (unneeded) */
repeat 3 
	stream.Read_DWORD();
	
GlobalFree(buf);
srowset_ptr = this+0x24;
```

We found the `SRowset` pointer in a function parameter `(EBP+0xC)` of an internal call,
once we get to read past the header.

Our steps to get the pointer are (see Connect.cpp).

1. Using Deviare-InProc we hook into `OLE32.dll!CreateStreamOnHGlobal` call.
2. On `ole32.dll!CreateStreamOnHGlobal` call, we look for the NK2 header in the created stream;
   in that case, we subsequently hook Read and Release methods of the IStream interface.
3. For every `IStream::Read` call we wait for reading past the initial 12-byte metadata header.
   Once there, we store the pointer by traversing the EBP chain to look for the third pointer
   `(EBP+0xC)` of the calling function.
4. When the `IStream::Release` is called for the NK2 stream, we create the `CNicknameCache` class
   passing the `SRowSet` structure pointer we obtained in the process. This class acts as a simple
   wrapper for the database: you can obtain row count, sort by tag, get/set properties, swap
   rows and retrieve a particular row (`SRow` structure pointer).
5. At this point we're ready to fiddle with the rowset structure without problem.  Outlook will  
   write it to disk when at application exit.
   
How to run the sample
=====================
1. Make sure Outlook is properly installed.
2. Open and build the solution.
3. Open Outlook. When you open the compose mail window, a Nektra ribbon tab with the UI button
   should be available. 
4. Click the button to open the editor and modify the list entries as you wish.
5. Play with the autocomplete dropdown on the CC/BCC input fields to see the effect of your 
   modification on the input data and the field ordering.

After Outlook saves your modifications, you can use an external NK2 viewer to see your modified entries. [5]

References
==========
[1] http://portalvhds6gyn3khqwmgzd.blob.core.windows.net/files/NK2/NK2WithBinaryExample.pdf
[2] SRowset https://msdn.microsoft.com/en-us/library/ms629453(v=vs.85).aspx
[3] SRow https://msdn.microsoft.com/en-us/library/ms629452(v=vs.85).aspx
[4] Nickname Cache https://msdn.microsoft.com/en-us/library/ms629452(v=vs.85).aspx
[5] http://www.nirsoft.net/utils/outlook_nk2_edit.html
	
