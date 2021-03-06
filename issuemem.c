/*
 * This file is part of GetHT
 *
 * See COPYING file for copyright, license and warranty details.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "getht.h"

void nogo_mem()
/*	called if memory assignation fails
 *	TODO: handle freeing of memory to avoid leaks */
{
	fprintf(stderr, "Could not assign memory, exitting\n");
	exit(1);
}

iss ** assignnew_iss(iss ** issue, int *no_of_issues)
/* assign memory for new issue */
{
	iss ** tmp = NULL;

	if(*no_of_issues < 0)
	{       /* make issue** a new array of issue pointers */
		if( (tmp = malloc(sizeof(iss *))) == NULL )
			nogo_mem();
	}
	else
	{       /* add a new pointer to issue pointer list */
		if( (tmp = realloc(issue, sizeof(iss *) + (((*no_of_issues)+1) * sizeof(iss *)))) == NULL )
			nogo_mem();
	}

	(*no_of_issues)++;
	
	/* make new array item a pointer to issue */
	if( (tmp[*no_of_issues] = malloc(sizeof(iss))) == NULL )
		nogo_mem();

	return tmp;
}

sec ** assignnew_sec(sec ** section, int *no_of_sections)
/* assign memory for new section */
{
	sec ** tmp = NULL;

	if(*no_of_sections < 0)
	{       /* make **section a new array of section pointers */
		if( (tmp = malloc(sizeof(sec *))) == NULL )
			nogo_mem();
	}
	else
	{       /* add a new pointer to section pointer list */
		if( (tmp = realloc(section, sizeof(sec *) + (((*no_of_sections)+1) * sizeof(sec *)))) == NULL )
			nogo_mem();
	}
	
	(*no_of_sections)++;

	/* make new array item a pointer to issue */
	if( (tmp[*no_of_sections] = malloc(sizeof(sec))) == NULL )
		nogo_mem();

	return tmp;
}

it ** assignnew_it(it ** item, int * no_of_items)
{
	it ** tmp = NULL;

	if(*no_of_items < 0)
	{       /* make **item a new array of item pointers */
		if( (tmp = malloc(sizeof(it *))) == NULL )
			nogo_mem();
										                        }
	else
	{       /* add a new pointer to item pointer list */
		if( (tmp = realloc(item, sizeof(it *) + (((*no_of_items)+1) * sizeof(it *)))) == NULL )
			nogo_mem();
	}

	(*no_of_items)++;

	/* make new array item a pointer to item */
	if( (tmp[*no_of_items] = malloc(sizeof(it))) == NULL )
		nogo_mem();

	return tmp;
}

int issuesort(iss ** issue, int no_of_issues)
/* does a basic bubble sort, by date, returning sorted issue */
{
	int sortindex[no_of_issues];

	int count1, count2, temp;
	
	for(count1 = 0; count1 <= no_of_issues; count1++)
		sortindex[count1] = count1;

	/* find correct order of issues using a bubble sort */
	for(count1 = 0; count1 <=no_of_issues; count1++)
	{
		for(count2 = 0; count2 < no_of_issues; count2++)
		{
			if(issue[sortindex[count2]]->date.year < issue[sortindex[count2+1]]->date.year)
			{
				temp = sortindex[count2];
				sortindex[count2] = sortindex[count2+1];
				sortindex[count2+1] = temp;
			}
			else if((issue[sortindex[count2]]->date.year == issue[sortindex[count2+1]]->date.year) &&
				(issue[sortindex[count2]]->date.firstmonth < issue[sortindex[count2+1]]->date.firstmonth))
			{
				temp = sortindex[count2];
				sortindex[count2] = sortindex[count2+1];
				sortindex[count2+1] = temp;
			}
		}
	}

	iss * sortedissue[no_of_issues];

	for(count1 = 0; count1 <= no_of_issues; count1++)
		sortedissue[count1] = issue[sortindex[count1]];

	for(count1 = 0; count1 <= no_of_issues; count1++)
		issue[count1] = sortedissue[count1];

	return 0;
}
