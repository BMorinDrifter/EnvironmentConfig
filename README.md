EnvironmentConfig
=====

Purpose
-------

EnvironmentConfig is a simple little Unreal Engine plug-in to simplify using a single
build artifact to talk to multiple backend environments.

Usage (General)
---------------
EnvironmentConfig loads settings into your Game.ini configuration set via 3 files per
environment

`Game\Config\Environment\<EnvironmentName>\Client.ini`

`Game\Config\Environment\<EnvironmentName>\Common.ini`

`Game\Config\Environment\<EnvironmentName>\Server.ini`

- All build targets load Common.ini
- Dedicated Game Servers load Server.ini
- All other targets load Client.ini
- The Unreal Editor loads both with priority to Server.ini

**EnvironmentConfig is not indended for storing any secrects or keys**

Usage (Client)
--------------
The default environment is Integration.  Pass Env=<EnvironmentName> on the 
command line to use a different environment.

Epic Launcher does not have a way to modify the command line for different 
environments, instead it passes epicsandboxid on the command line and you will
need to map that into an environment.

Usage (Server)
--------------
Setting the environment on the command line works great for debugging and
fleet based solutions (AWS Gamelift, Agnoes, etc.)  For container based
game server deployment, the environment variable GAME_ENVIRONMENT can be used
instead.  GAME_ENVIRONMENT is only checked from dedicated servers.

License
-------

This project is licensed under the Apache-2.0 License.

Contribution
------------

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, as defined in the Apache-2.0 license, shall be
licensed as above, without any additional terms or conditions.

Credit
------

Thanks to Ray Davis (CEO Drifter) for giving me permission to open source this solution.
