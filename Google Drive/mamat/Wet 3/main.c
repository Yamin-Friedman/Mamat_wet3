/**includes**/
#include "defs.h"
#include "Battlefield.h"
typedef struct _Command {
	char command[MAX_INPUT_LINE];
	int  index;
} Command;

typedef struct _Command *PCommand;
//Command Functions
char* Command_Get_Command(PCommand command) {
	return command->command;
}

int Command_Get_Index(PCommand command) {
	return command->index;
}

PCommand Command_Create(char *command, int index) {
	PCommand new_command = (PCommand)malloc(sizeof(Command));
	if (new_command == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(new_command->command, command);
	new_command->index = index;
}

void Command_Delete(PCommand command) {
	if (command == NULL) {
		return;
	}
	free(command);
}
// Commands User Functions

PElem Command_Clone_Func(PElem pelem) {

	PCommand new_command = Command_Create(Command_Get_Command((PCommand)pelem), Command_Get_Index((PCommand)pelem));
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return new_command;
}

void Command_Destroy_Func(PElem pelem) {
	if (pelem == NULL) {
		return;
	}
	Command_Delete((PCommand)pelem);
}

bool Command_Compare_Keys_Func(PKey pkey1, PKey pkey2) {
	if (pkey1 == NULL || pkey2 == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}

	if (strcmp((char*)pkey1, (char*)pkey2) == 0) {
		return true;
	}
	return false;
}

void Command_Print_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	printf("%s/n", Command_Get_Command((PCommand)pelem));
}

PKey Command_Get_Key(PElem pelem) {
	PKey key = NULL;

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	Command_Get_Command((PCommand)pelem, key);

	return key;
}
//other functions



int main() {

	/**Main Initialize**/

	//1) Program Starts with Commands List
	PList Commands_List = List_Create(Command_Clone_Func, Command_Destroy_Func, Command_Compare_Keys_Func, Command_Print_Func, Command_Get_Key);
	if (Commands_List == NULL) {
		printf("Program Init Error\n");
		return EXIT_FAILURE;
	}

	//2) Battlefield List
	bool Battlefield_Created = false;
	bool ended = false;

	//3) /**STRTOK**
	/**Need two copies of program's input line: one for each strtok.(because strtok changes it's input string)**/
	char Input_Line[MAX_INPUT_LINE] = { 0 };				// stores program's input line by line
	char Input_Line_Copy[MAX_INPUT_LINE] = { 0 };
	char delimiters[] = " \t\n";
	int Args_Num;											// number of arguments in current command
	char* Curr_Command_Index;								//	will hold the current command index
	char* Command_Arguments[MAX_ARG];						//	all command's arguments after strtok completed.


	//4) Main LOOP

	while (!ended) {												//program didnt end
		fgets(Input_Line, MAX_INPUT_LINE, stdin);					//scan next input line
		strcpy(Input_Line_Copy, Input_Line);						//making backup of input line (going to use strtok)
		Curr_Command_Index = strtok(Input_Line_Copy, delimiters);	//getting the index of current command - copied string Changed!

		/**Cases according to command's index**/

		//C.1) index is "Exe" - need to execute all commands by current order
		if (!strcmp(Curr_Command_Index, "Exe")) {


		}
	}

}












