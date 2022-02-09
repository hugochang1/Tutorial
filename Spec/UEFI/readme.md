
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
