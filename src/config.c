/*
 * Copyright 2006 Nick White
 *
 * This file is part of GetHT
 * 
 * GetHT is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GetHT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GetHT; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include <string.h>

#include "getht.h"

extern proxytype proxy_type;
extern char proxy_addr[STR_MAX];
extern long proxy_port;
extern proxyauth proxy_auth;
extern char proxy_user[STR_MAX];
extern char proxy_pass[STR_MAX];

int loadconfig(char * htde_path, char * issue_path, int * update)
/*	Loads variables from config file to extern and passed
 *	variables. */
{
	FILE * config_file;
	char filepath[STR_MAX];

	snprintf(filepath, STR_MAX, "%s/config.ini", htde_path);

	if((config_file = fopen(filepath,"r")) == NULL)
	{
		fprintf(stderr,"Cannot open file %s for reading.\n",filepath);
		return 1;
	}

	char parameter[80], option[80];
	while(!feof(config_file))
	{
		fscanf(config_file, "%s = %s", option, parameter);

		if(option[0] == '#');	/* ignore lines beginning with a hash */
		else if(!strcmp(option, "issuepath"))
			strncpy(issue_path, parameter, STR_MAX);
		else if(!strcmp(option, "startup_check"))
			*update = atoi(parameter);
		else if(!strcmp(option, "proxy_type"))
		{
			if(!strcmp(parameter, "http"))
				proxy_type = HTTP;
			else if(!strcmp(parameter, "socks4"))
				proxy_type = SOCKS4;
			else if(!strcmp(parameter, "socks5"))
				proxy_type = SOCKS5;
			else
				fprintf(stderr,
					"Proxy type %s not known, please use either http, socks4 or socks5",
					parameter);
		}
		else if(!strcmp(option, "proxy_address"))
			strncpy(proxy_addr, parameter, STR_MAX);
		else if(!strcmp(option, "proxy_port"))
			proxy_port = (long) atoi(parameter);
		else if(!strcmp(option, "proxy_auth"))
		{
			if(!strcmp(parameter, "basic"))
				proxy_auth = BASIC;
			else if(!strcmp(parameter, "digest"))
				proxy_auth = DIGEST;
			else if(!strcmp(parameter, "ntlm"))
				proxy_auth = NTLM;
			else
				fprintf(stderr,
					"Proxy authentication method %s not known, please use basic, digest or ntlm",
					parameter);
		}
		else if(!strcmp(option, "proxy_user"))
			strncpy(proxy_user, parameter, STR_MAX);
		else if(!strcmp(option, "proxy_pass"))
			strncpy(proxy_pass, parameter, STR_MAX);
		else
			fprintf(stderr, "Option '%s' not recognised, ignoring\n", option);
	}

	return 0;
}

int writefreshconfig(char * htde_path, char * issue_path, int * update)
/*	Write a new config file according to extern and passed variables. */
{
	FILE * config_file;
	char filepath[STR_MAX];

	snprintf(filepath, STR_MAX, "%s/config.ini", htde_path);

	if((config_file = fopen(filepath,"w")) == NULL)
	{
		fprintf(stderr,"Cannot open file %s for writing.\n",filepath);
		return 1;
	}
	else
		fprintf(stdout,"Writing a fresh config file to %s.\n",filepath);

	if(issue_path[0])
		fprintf(config_file, "%s = %s\n", "issuepath", issue_path);
	if(update)
		fprintf(config_file, "%s = %i\n", "startup_check", *update);
	if(proxy_type != NONE)
	{
		if(proxy_type = HTTP)
			fprintf(config_file, "%s = %s\n", "proxy_type", "http");
		else if(proxy_type = SOCKS4)
			fprintf(config_file, "%s = %s\n", "proxy_type", "socks4");
		else if(proxy_type = SOCKS5)
			fprintf(config_file, "%s = %s\n", "proxy_type", "socks5");
	}
	if(proxy_addr[0])
		fprintf(config_file, "%s = %s\n", "proxy_address", proxy_addr);
	if(proxy_port)
		fprintf(config_file, "%s = %i\n", "proxy_port", proxy_port);
	if(proxy_auth != NOAUTH)
	{
		if(proxy_auth = BASIC)
			fprintf(config_file, "%s = %s\n", "proxy_auth", "basic");
		else if(proxy_auth = DIGEST)
			fprintf(config_file, "%s = %s\n", "proxy_auth", "digest");
		else if(proxy_auth = NTLM)
			fprintf(config_file, "%s = %s\n", "proxy_auth", "ntlm");
	}
	if(proxy_user[0])
		fprintf(config_file, "%s = %s\n", "proxy_user", proxy_user);
	if(proxy_pass[0])
		fprintf(config_file, "%s = %s\n", "proxy_pass", proxy_pass);
		
	return 0;
}

int updateconfig(char * htde_path, char * issue_path, int * update)
/*	Read existing config file, and rewrite any variables which differ
 *	in memory. */
{
	FILE * config_file;
	char filepath[STR_MAX];

	snprintf(filepath, STR_MAX, "%s/config.ini", htde_path);

	if((config_file = fopen(filepath,"rw")) == NULL)
	{
		fprintf(stderr,"Cannot open file %s for reading/writing.\n",filepath);
		return 1;
	}

	fprintf(stderr,"Not yet implemented.\n");

	return 1;
}