#pragma once

// maximum number of accounts in 1-one session
static const unsigned short MAX_PEOPLE = 1024;

// default value for private data members
static const std::string _NULL = "null";

// UI
static const char* header =
"\n\n\t*	*	*   \"Bank Management System\"    *	*	*";

static const char* menu =
	"\n\n\tChoose the operation:"
	"\n\n\'C\' = Create new account"
	"\n\n\'L\' = Sign in via account.txt"
	"\n\n\'R\' = Sign in via custom file"
	"\n\nEnter = Manual input"
	"\n\n\nCURRENT USER: "
	"\t";

static const char* services =
	"\n\n\tServices List"
	"\n\n\'T\' = Transfer"
	"\n\n\'U\' = Top-up";
