#pragma once
#include <iostream>
#include <string>
#include "account.h"
using namespace std;

// maximum number of accounts in 1-one session
static const unsigned short MAX_PEOPLE = 1024;

// default value for private data members
static const string _NULL = "null";

// UI
static const char* header =
"\n\n\t*	*	*   \"Bank Management System\"    *	*	*";

static const char* menu =
	"\n\n\tChoose the operation:"
	"\n\n\'C\' = Create new account"
	"\n\n\'L\' = Sign in via account.txt"
	"\n\n\'R\' = Sign in via custom file"
	"\n\n\'M\' = Manual input"
	"\n\n\'E\' = Safe exit"
	"\t";

static const char* operations =
	"\n\n\tServices List"
	"\n\n\'T\' = Transfer"
	"\n\n\'U\' = Top-up"
	"\n\n\'D\' = Display"
	"\n\n\'E\' = Safe exit"
	"\t";