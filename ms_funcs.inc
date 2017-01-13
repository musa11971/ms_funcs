#if defined ms_funcs_included
    #endinput
#endif

#define ms_funcs_included
#include <a_samp>
#include <a_http>
#include <foreach>

static msf_Nametag[MAX_PLAYERS]; 			// Nametag visible? 1 Yes, 0 No
static msf_RconPass[500]; 					// Server RCON password
static msf_Country[MAX_PLAYERS][100];		// Players country
static msf_CountryCode[MAX_PLAYERS][100];	// Players country code
static msf_City[MAX_PLAYERS][100];			// Players city

/////////////////////////////////////////////////////////////////////////////////////

stock ShowPlayerNametag(playerid, msf_Toggle = 0)
{
	if(!IsPlayerConnected(playerid) || (msf_Toggle != 0 && msf_Toggle != 1)) return 0;
	msf_Nametag[playerid] = msf_Toggle;

	foreach(Player, i)
	{
		ShowPlayerNameTagForPlayer(i, playerid, msf_Toggle);
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////

stock IsPlayerNametagShown(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	return msf_Nametag[playerid];
}

/////////////////////////////////////////////////////////////////////////////////////

stock GenerateRCONPassword(length = 20)
{
	static string[500];
	while(length--)
		string[length] = random(2) ? (random(26) + (random(2) ? 'a' : 'A')) : (random(10) + '0');
	format(msf_RconPass, sizeof(msf_RconPass), "%s", string);
	format(string, sizeof(string), "rcon_password %s", string);
	SendRconCommand(string);
}

/////////////////////////////////////////////////////////////////////////////////////

stock GetRCONPassword() return msf_RconPass;

/////////////////////////////////////////////////////////////////////////////////////

stock GetPlayerCountry(playerid) return msf_Country[playerid];
stock GetPlayerCity(playerid) return msf_City[playerid];
stock GetPlayerCountryCode(playerid) return msf_CountryCode[playerid];

/////////////////////////////////////////////////////////////////////////////////////

forward msf_GetCountry(index, response_code, data[]);
public msf_GetCountry(index, response_code, data[])
{
    new msf_tempposition = strfind(data, "country_name\":\"", true) + 15;
    strdel(data, 0, msf_tempposition);
    msf_tempposition = strfind(data, "\"", true);
    strdel(data, msf_tempposition, strlen(data));

    format(msf_Country[index], 100, "%s", data);
    return 1;
}

forward msf_GetCountryCode(index, response_code, data[]);
public msf_GetCountryCode(index, response_code, data[])
{
    new msf_tempposition = strfind(data, "country_code\":\"", true) + 15;
    strdel(data, 0, msf_tempposition);
    msf_tempposition = strfind(data, "\"", true);
    strdel(data, msf_tempposition, strlen(data));

    format(msf_CountryCode[index], 10, "%s", data);
    return 1;
}

forward msf_GetCity(index, response_code, data[]);
public msf_GetCity(index, response_code, data[])
{
    new msf_tempposition = strfind(data, "city\":\"", true) + 7;
    strdel(data, 0, msf_tempposition);
    msf_tempposition = strfind(data, "\"", true);
    strdel(data, msf_tempposition, strlen(data));

    format(msf_City[index], 100, "%s", data);
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////

public OnPlayerStreamIn(playerid, forplayerid)
{
	if(!msf_Nametag[playerid]) ShowPlayerNameTagForPlayer(forplayerid, playerid, 0);

    #if defined ms_funcs_OnPlayerStreamIn
    	return ms_funcs_OnPlayerStreamIn(playerid, forplayerid); 
    #else 
    	return 1;
    #endif 
}

// OnPlayerStreamIn
#if defined _ALS_OnPlayerStreamIn
    #undef OnPlayerStreamIn
#else
    #define _ALS_OnPlayerStreamIn
#endif 

#define OnPlayerStreamIn ms_funcs_OnPlayerStreamIn

#if defined ms_funcs_OnPlayerStreamIn
	forward ms_funcs_OnPlayerStreamIn(playerid, forplayerid);
#endif

/////////////////////////////////////////////////////////////////////////////////////

public OnPlayerConnect(playerid)
{
	// Display player nametag by default
	msf_Nametag[playerid] = true;

	// Geolocation
	static ip[39];
	GetPlayerIp(playerid, ip, sizeof(ip));

	static url[60];
	format(url, sizeof(url), "freegeoip.net/json/%s", ip);

	HTTP(playerid, HTTP_GET, url, "", "msf_GetCountry");
	HTTP(playerid, HTTP_GET, url, "", "msf_GetCountryCode");
	HTTP(playerid, HTTP_GET, url, "", "msf_GetCity");

    #if defined ms_funcs_OnPlayerConnect
    	return ms_funcs_OnPlayerConnect(playerid); 
    #else 
    	return 1;
    #endif 
}

// OnPlayerConnect
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif 

#define OnPlayerConnect ms_funcs_OnPlayerConnect

#if defined ms_funcs_OnPlayerConnect
	forward ms_funcs_OnPlayerConnect(playerid);
#endif