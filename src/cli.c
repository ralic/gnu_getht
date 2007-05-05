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
#include <stdlib.h>
#include <string.h>

#include "issue.h"
#include "getht.h"

void list_issues(iss ** issue, int no_of_issues, int verbose)
{
	int iss_no, sec_no, it_no;
	for(iss_no=0;iss_no<=no_of_issues;iss_no++)
	{
		printf("[%i]\t", iss_no);
		printf("%s\n", issue[iss_no]->title);
		if(verbose >= 2)
			printf("Year: %i; Months: %i - %i\n",issue[iss_no]->date.year,issue[iss_no]->date.firstmonth,issue[iss_no]->date.lastmonth);
		if(verbose >= 1)
		{
			for(sec_no=0; sec_no<=issue[iss_no]->no_of_sections; sec_no++)
			{
				printf("\t%i: %s\n", issue[iss_no]->section[sec_no]->number,
					issue[iss_no]->section[sec_no]->title);
				printf("\t%s\n", issue[iss_no]->section[sec_no]->uri);
				if(verbose >= 2)
				{
					for(it_no=0;
						it_no<=issue[iss_no]->section[sec_no]->no_of_items;
						it_no++)
					{
						printf("\t\tpp %i - %i: %s\n",
							issue[iss_no]->section[sec_no]->item[it_no]->firstpage,
							issue[iss_no]->section[sec_no]->item[it_no]->lastpage,
							issue[iss_no]->section[sec_no]->item[it_no]->title);
					}
				}
			}
		}
	}
}

void list_media(iss ** issue, int no_of_issues, int verbose)
{
	int iss_no, med_no, med_global;
	for(iss_no=0, med_global=0;iss_no<=no_of_issues;iss_no++)
	{
		if(issue[iss_no]->no_of_media >= 0)
		{
			printf("%s\n", issue[iss_no]->title);
			if(verbose >= 2)
				printf("Year: %i; Months: %i - %i\n",issue[iss_no]->date.year,issue[iss_no]->date.firstmonth,issue[iss_no]->date.lastmonth);
			for(med_no=0; med_no <= (issue[iss_no]->no_of_media); med_no++, med_global++)
			{
				printf("[%i]\t", med_global);
				printf("%s\n", issue[iss_no]->media[med_no]->title);
				if(verbose >= 1)
				{
					printf("\t%s\n", issue[iss_no]->media[med_no]->uri);
					if(verbose >=2)
					{
						if(issue[iss_no]->media[med_no]->comment[0]!='\0')
							printf("\t%s\n", issue[iss_no]->media[med_no]->comment);
					}
				}
			}
		}
	}
}

void showusage()
{
	printf("Usage: getht [-ualmofhv] [-d issno] [-n medno] [-t tocfile]\n");
	printf("-u | --update                 Update contents files\n");
	printf("-a | --download-all           Download all issues\n");
	printf("-d | --download-issue issno   Download issue number issno\n");
	printf("-n | --download-media medno   Download media number n\n");
	printf("-o | --download-all-media     Download all media\n");
	printf("-f | --force                  Force re-download of existing files\n");
	printf("-l | --list-issues            List available issues\n");
	printf("-m | --list-media             List available media\n");
	printf("-t | --tocfile file           Use alternative contents xml file\n");
	printf("-x | --mediatocfile file      Use alternative media contents xml file\n");
	printf("-h | --help                   Print this help message\n");
	printf("-v | --verbose                Make output more verbose\n");
	printf("-V | --version                Print version information\n");
}
