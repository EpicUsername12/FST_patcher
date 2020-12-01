# FST_patcher
Patcher for WiiU title's FST file!

# Disclaimer
This exploit was found by Maschell in private discussions inside the [4TU discord server](http://fortheusers.org/)
This is just my implementation + patcher

# How does it works
It will make each File/Dir entry in the [FST file](http://wiiubrew.org/wiki/FST) point to a secondary header with flags 0x0200
The IOSU, then, will not check if the data is signed or not (it means, you can alter /code, /content, /meta and the IOSU will simply ignore)

The patched title needs to be a VALID title at first (system titles, eshop games, etc..)

**DO NOT ALTER OSv10, YOU WILL BRICK ANYWAYS**

# What can we do?
Patch a title, then modify it's rpx and give codegen access, allowing for free-of-charge coldboot under a system title. (such as Health and Safety, WiiU chat, Daily Log, etc..)

Just need someone to do it, Maschell had a great free new colboot homebrew environment, but still nothing is public or released.

# Video tutorial: HBL under WiiU Chat (on a stock console, not running CFW)
https://www.youtube.com/watch?v=ZMmKAt3NI78


# How to unpatch a title
- Remove the every file and subdirectories from: /code, /content, /meta
- Reinstall the title (downloaded from JNUSTool with -dlEncrypted)
