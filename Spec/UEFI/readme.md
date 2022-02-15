
|Term|Full|Description|
|-|-|-|
|PI|Platform Initialization|SEC + PEI + DXE + BSD|
|EDK|EFI Developer Kit|A modern, feature-rich, cross-platform firmware development environment for the UEFI and PI specifications|
|SEC|Security||
|PEI|Pre-EFI Initialization||
|PEIM|PEI Module|modular chunks of firwmare in PEI|
|PPI|PEIM-to-PEIM Interface|in DXE|
|PHIT|PEI Hand-off Information Table|PEI generated -> DXE used|
|HOBs|Hand-off blocks|PEI generated -> DXE used|
|DXE|Driver Execution Environment||
|BDS|Boot Device Selection||
|TSL|Transient System Load||
|BS|Boot Service||
|RT|Runtime||
|AL|After Life||
|FV|Firmware Volume|a logical repository for FW data + code|
|BFV|Boot Firmware Volume|where PEI code is stored|
|AP|Architectureal Protocol|in DEX|
|CAR|Cache as RAM|in PEI|
|T-RAM|temporary RAM|in PEI|
|XIP|Execute In Place|PEIM run on flash instaed of RAM|
|DEPEX|Dependency Expression||
|DXE IPL|DXE Initial Program Loader|the code that transitions the DXE core code into memory|
|BSP|Boot Strap Processor||
|ESP|EFI System Partition||
|SMM|System Management Mode|in DXE|
|HII|Human Interface Infrastucture|in BDS|
|IFR|Internal Form Representation|in BDS|
|VFR|Visual Form Representation|in BDS|
|OVMF|Open Virtual Machine Firmware||

````
void dump_EFI_GUID(IN CONST EFI_GUID* guid)
{
  DEBUG ((DEBUG_INFO, "hugo dump_EFI_GUID %x-%x-%x-%02x%02x%02x%02x%02x%02x%02x%02x\n",
  	guid->Data1, guid->Data2, guid->Data3,
  	guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3], 
  	guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]));
}
dump_EFI_GUID(&gEfiDxeIplPpiGuid);

//return 0 menas guid1 and guid2 are same, otherwise return 1
BOOLEAN is_equal_EFI_GUID(IN CONST EFI_GUID* guid1, IN CONST EFI_GUID* guid2)
{
	if ( ((INT32 *)guid1)[0] == ((INT32 *)guid2)[0] &&
		((INT32 *)guid1)[1] == ((INT32 *)guid2)[1] &&
		((INT32 *)guid1)[2] == ((INT32 *)guid2)[2] &&
		((INT32 *)guid1)[3] == ((INT32 *)guid2)[3]	) {
		return FALSE;
	}
	return TRUE;
}
is_equal_EFI_GUID(&guid1, &guid2);

````
