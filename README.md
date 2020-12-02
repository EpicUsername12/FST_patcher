# FSTPatcher
This patcher will let you arbitrarily modify the code and contents of any *legitimate* title.

[Demo Video](https://www.youtube.com/watch?v=ZMmKAt3NI78)

# Disclaimer
This exploit was found by Maschell in private discussions inside the [4TU Discord server](http://fortheusers.org/).

This is just my implementation and patcher.

# How it works
Each file/directory entry in the [FST file](http://wiiubrew.org/wiki/FST) will be modified to point to a secondary header with flags 0x0200

IOSU then will not properly check the title, and therefore `/code`, `/content`, and `/meta` are freely editable.

The original title needs to be a real Nintendo title (NOT a custom channel), and there are various free titles that can be patched.

**DO NOT ALTER OSv10, YOU WILL DEFINITELY BRICK**

# What can we do?
Patch a title, then modify it's rpx and give codegen access, allowing for free-of-charge coldboot under a system title. (such as Health and Safety, WiiU chat, Daily Log, etc..)

Just need someone to do it, Maschell had a great free new colboot homebrew environment, but still nothing is public or released.

# How to unpatch a title
- Remove the every file and subdirectories from: /code, /content, /meta
- Reinstall the title (downloaded from JNUSTool with -dlEncrypted)
