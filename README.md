# Celerity
(noun) swiftness of movement

Minecraft server in C++

Full handshaking, login, (online-mode) auth, encryption, and compression is implemented.

Working on Configuration state, then will look at the Play state.

# To Build

Before building, you have to install [vcpkg](https://github.com/microsoft/vcpkg) and bootstrap it. Then create a `CMakeUserPresets.json` file in the root of the project that sets the `VCPKG_ROOT` environment variable. This file is not checked in to Git since the value of the environment variable is...variable.

Example `CMakeUserPresets.json`:
```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "<absolute path to vcpkg>"
      }
    }
  ]
}
```
