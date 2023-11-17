# MCCPP
Minecraft server in C++

Only handshaking, status request, ping request, status response, ping response, and login start are implemented.

Status response is hard coded for simplicity.

## Update: 11/17/23 0358 PST
Now creates an rsa keypair on startup, shoves networking in own thread, and 
handles login start. Investigating proto encryption, then maybe compression. If that goes anywhere, I'll
look into authentication. At that point, I'm kinda deep. I have no idea where I'd start with worldgen
or actually spawning a player in a world, but...we'll see.