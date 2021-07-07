# CORBA-OmniOrb-Example

## Requirements:
* omniORB 4.2;
* build-essential: gcc, g++, make...

## Use:
```
$$ make
$$ # -----------------
$$ # Remove old files (before restart omniNames):
$$ # sudo rm -rf /opt/omni/omniNamesLogdir/* /opt/omni/omniNamesDatadir/* /opt/omni/omniNamesError.txt
$$ # -----------------
$1 sudo omniNames -start -logdir /opt/omni/omniNamesLogdir -errlog /opt/omni/omniNamesError.txt -ORBInitRef "NameService=corbaloc::localhost:2809/NameService"
$2 ./ServerRun -ORBInitRef NameService=corbaloc::localhost:2809/NameService
$3 ./ClientRun -ORBInitRef NameService=corbaloc::localhost:2809/NameService
```

## Output

### Server
```
IOR:010000001600000049444c3a446174612f53657276696365413a312e30000000010000000000000064000000010102000e0000003139322e3136382e312e3230310091a30e000000fe7ca4e56000003ceb000000000000000200000000000000080000000100000000545441010000001c00000001000000010001000100000001000105090101000100000009010100
```
### Client
```
Response (HelloWorld): Hello, world!
Response (Div, 10/2): 2 (div error: 0)
Response (CaesarCipher): Khoor, zruog!
```