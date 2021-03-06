# ms_funcs
GitHub repository for the ms_funcs include for SA-MP. ms_funcs offers a variety of easy to use scripting functions to develop scripts faster and more neat.

## Functions

`ShowPlayerNameTag(playerid, toggle);`  
Toggle the display of a players nametag (above their head).  
Returns **true** if success, **false** if failure.  

`IsPlayerNametagShown(playerid);`  
Find out if the players nametag is currently hidden or shown.  
Returns **true** if the nametag is shown, **false** if it's hidden.

`GenerateRCONPassword(length = 20);`  
Generate and set a unique RCON password.  

`GetRCONPassword();`  
Get the RCON password generated with the *GenerateRCONPassword* function.  
Returns the password.

`GetPlayerCountry(playerid);`  
Get the players country, based on IP.  
This does **not** work on local servers.  
Returns the full country name. Example: "United Kingdom"  

`GetPlayerCountryCode(playerid);`  
Get the players country code, based on IP.  
This does **not** work on local servers.  
Returns the full country code. Example: "UK"

`GetPlayerCity(playerid);`  
Get the players city name, based on IP.  
This does **not** work on local servers.  
Returns the full city name. Example: "London"
