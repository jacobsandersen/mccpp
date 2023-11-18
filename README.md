# MCCPP
Minecraft server in C++

Only handshaking, status request, ping request, status response, ping response, and login start are implemented.

Status response is hard coded for simplicity.

## Update: 11/17/23 0358 PDT
Now creates an rsa keypair on startup, shoves networking in own thread, and 
handles login start. Investigating proto encryption, then maybe compression. If that goes anywhere, I'll
look into authentication. At that point, I'm kinda deep. I have no idea where I'd start with worldgen
or actually spawning a player in a world, but...we'll see.

## Update 11/17/23 1831 PDT
Now accepts login start and sends an encryption request and successfully receives the encryption response.
Next on this list would be to send authentication to Mojang authserver, get that response, and send a 
login success to move onto the configuration stage.