# What is FSTPatcher?
FSTPatcher is a proof-of-concept implementation of the FST pointer vulnerability for the Wii U.
This patcher, using that vuln, will let you arbitrarily modify the code and contents of a _legitimately installed_ title.

In the future, FSTPatcher may be used for gaining persistence in a more developed and user-ready coldboot exploit chain, but currently it is not expected to be supported except as a developers' curiosity.

View the [Demo Video](https://www.youtube.com/watch?v=ZMmKAt3NI78) for an example of what's possible currently.

# What _doesn't_ it do?

### First off, this is not a complete coldboot exploit chain.
> This is not even a complete exploit chain - it is an implementation of one key aspect (the persistence phase) of an in-development exploit chain, which may be used in the Wii U homebrew installation process in the future.
### This does not install the Homebrew channel.
> This only performs the FST pointer rewrite necessary to gain persistent, on-boot or on-title-launch arbitrary code execution on the Wii U.
### This does not allow piracy.
> The Wii U has "Technological Protection Measures", *c.f., DMCA*, enforced cryptographically, which prevent the unauthorized copying or installation of copied title data and license/"ticket" information. This tool does NOT circumvent, inhibit, prohibit, emulate or otherwise tamper with those functions.
> **Do not ask us to make it do that.** That is entirely outside of the scope of intent for this project.

# Disclaimer
This vulnerability was found by Maschell in private discussions inside the [4TU Discord server](http://fortheusers.org/).

This is just my implementation of the exploit and patcher.

# How it works
Each file/directory entry in the [FST file](http://wiiubrew.org/wiki/FST) will be modified to point to a secondary header with flags 0x0200

IOSU then will not properly check the title, and therefore `/code`, `/content`, and `/meta` are freely editable.

**The original title needs to be a proper, authorized title** (NOT a custom channel or pirate content). There are several free/preinstalled titles that can be patched.

**Furthermore, DO NOT ALTER THE OSv10 CONTENT, TITLE OR METADATA; YOU WILL DEFINITELY BRICK YOUR CONSOLE.**

# What can we do?
Patch and replace code in an application, then modify it's rpx and give codegen access, allowing for persistent homebrew program loading capability under a pre-installed system application (such as Health and Safety, WiiU chat, Daily Log, etc..)

# What's needed from here?
A lot. We need the full boot chain to be further implemented to allow safe and accessible homebrew, automatically at boot-time, and with a better user experience.
The 4TU group, alongside Maschell, had worked on a new homebrew environment, but still nothing is public or released.

# How to unpatch a title (and uninstall this exploit)
- Remove the every file and subdirectories from: /code, /content, /meta
- Reinstall the title (downloaded from JNUSTool with -dlEncrypted).
