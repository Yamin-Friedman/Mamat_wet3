/**includes**/
#include "defs.h"
#include "Battlefield.h"
#pragma warning(disable: 4996)
typedef struct _Command {
	char command[MAX_INPUT_LINE];
	char index[MAX_INPUT_LINE];
	char *command_args[MAX_ARG];
	int arg_num;
} Command;

typedef struct _Command *PCommand;
//Command Functions
char* Command_Get_Command(PCommand command) {
	return command->command;
}

char* Command_Get_Index(PCommand command) {
	return command->index;
}

char** Command_Get_Arguments(PCommand command) {
	return command->command_args;
}

int Command_Get_Arg_Num(PCommand command) {
	return command->arg_num;
}

PCommand Command_Create(char *command, char *index, char **command_args, int arg_num) {
	PCommand new_command = (PCommand)malloc(sizeof(Command));
	if (new_command == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	if (command != NULL)
		strcpy(new_command->command, command);
	if (index != NULL)
		strcpy(new_command->index, index);
	new_command->command_args;
	new_command->arg_num = arg_num;
	for (int i = 0; i < MAX_ARG; i++) {
		new_command->command_args[i] = (char*)malloc(MAX_INPUT_LINE);
	}
	int i = 0;
	while ((command_args[i] != NULL)&&(i<arg_num)){
		strcpy(new_command->command_args[i], command_args[i]);
		i++;
	}
	return new_command;
}

void Command_Delete(PCommand command) {
	if (command == NULL) {
		return;
	}
	for (int i = 0; i < MAX_ARG; i++) {
		free(command->command_args[i]);
	}
	free(command);
}
// Commands User Functions
PElem Command_Clone_Func(PElem pelem) {

	PCommand new_command = Command_Create(Command_Get_Command((PCommand)pelem), Command_Get_Index((PCommand)pelem), 
		Command_Get_Arguments((PCommand)pelem), Command_Get_Arg_Num((PCommand)pelem));
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

	key = Command_Get_Index((PCommand)pelem);

	return key;
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
// :)!!
//Don't Worry, Be Happy :)
int main() {

	/**Main Initialize**/

	//1) Program Starts with Commands List
	PList Commands_List = List_Create(Command_Clone_Func, Command_Destroy_Func, Command_Compare_Keys_Func, Command_Print_Func, Command_Get_Key);
	if (Commands_List == NULL) {
		printf("Program Init Error\n");
		return EXIT_FAILURE;
	}

	//2) Battlefield List
	PBattlefield pbattlefield = NULL;
	bool Battlefield_Created = false;
	bool ended = false;

	//3) /**STRTOK**
	/**Need two copies of program's input line: one for each strtok.(because strtok changes it's input string)**/
	char Input_Line[MAX_INPUT_LINE] = { 0 };				// stores program's input line by line
	char Input_Line_Copy[MAX_INPUT_LINE] = { 0 };
	char delimiters[] = " \t\n";
	int Args_Num;										// number of arguments in current command
	char* Curr_Command_Index;								// will hold the current command index
	char* Command_Arguments[MAX_ARG];// all command's arguments after strtok completed.
	for (int i = 0; i < MAX_ARG; i++) {
		Command_Arguments[i] = (char*)malloc(MAX_INPUT_LINE);
	}

	char *curr_strtok_value = NULL;
	PCommand Tmp_Command = NULL;
	Tmp_Command = Command_Create(NULL,0,Command_Arguments,0);
	//Tmp_Command->command_args[0] = NULL;
	//4) Main LOOP

	while (!ended) {												//program didnt end
		//initializing Curr_Command

		Args_Num = 0;
		fgets(Input_Line, MAX_INPUT_LINE, stdin);					//scan next input line
		if (Input_Line == NULL)
			continue;
		else
			strcpy(Input_Line_Copy, Input_Line);//making backup of input line (going to use strtok)
		Curr_Command_Index = strtok(Input_Line_Copy, delimiters);	//getting the index of current command - copied string Changed!
		if (Curr_Command_Index == NULL)
			continue;
		else
			strcpy(Tmp_Command->index, Curr_Command_Index);
		curr_strtok_value = strtok(NULL, delimiters);
		if (curr_strtok_value != NULL) {
			strcpy(Tmp_Command->command, curr_strtok_value);
		}
		Command_Arguments[Args_Num] = strtok(NULL, delimiters);
		while (Command_Arguments[Args_Num] != NULL)
		{
			strcpy(Tmp_Command->command_args[Args_Num], Command_Arguments[Args_Num]);
			Args_Num++;
			Command_Arguments[Args_Num] = strtok(NULL, delimiters);
		}
		Tmp_Command->arg_num = Args_Num;
		
		/**Cases according to command's index**/

		//C.1) index is "Exe" - need to execute all commands by current order
		if (strcmp(Curr_Command_Index, "Exe")!=0) {
			if (strcmp(Curr_Command_Index, "Exit")!=0){
				List_Add_Elem(Commands_List, Tmp_Command);
			}
			else {
		//C.2) index is "Exit"
				List_Delete(Commands_List);
				Command_Delete(Tmp_Command);
				if (Battlefield_Created = false) {
					return 0;
				}
				for (int i = 0; i < MAX_ARG; i++) {
					free(Command_Arguments[i]);
				}
				Battlefield_Delete(pbattlefield);
				return 0;
			}
		}
		else {
			int i = 1;
			char c[10];
			itoa(i,c,10);
			PCommand Curr_Command = List_Get_Elem(Commands_List, &c);
			while (Curr_Command)
			{
				//command execution
				if (strcmp(Curr_Command->command, "Create_B") == 0) {
					pbattlefield = Battlefield_Create();
					Battlefield_Created = true;
					printf("Battlefield Created!\n");
				}
				else if (strcmp(Curr_Command->command, "Add_W") == 0) {
					Battlefield_Add_WarZone(pbattlefield, Curr_Command->command_args[0]);
				}
				else if (strcmp(Curr_Command->command, "Del_W") == 0) {
					Battlefield_Delete_WarZone(pbattlefield, Curr_Command->command_args[0]);
				}
				else if (strcmp(Curr_Command->command, "R_W") == 0) {
					Battlefield_Warzone_Raise_Alert(Curr_Command->command_args[0], pbattlefield);
				}
				else if (strcmp(Curr_Command->command, "Add_Sq") == 0) {
					Battlefield_Add_Squad(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1]);
				}
				else if (strcmp(Curr_Command->command, "Del_Sq") == 0) {
					Battlefield_Delete_Squad(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1]);
				}
				else if (strcmp(Curr_Command->command, "M_Sq") == 0) {
					Batllefield_Move_Squad(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1], 
						Curr_Command->command_args[2]);
				}
				else if (strcmp(Curr_Command->command, "Add_Sold") == 0) {//need to check soldier position error 
					Battlefield_Add_Soldier(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1],
						Curr_Command->command_args[2], Curr_Command->command_args[3]);
				}
				else if (strcmp(Curr_Command->command, "Del_Sold") == 0) {
					Battlefield_Delete_Soldier(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1],
						Curr_Command->command_args[2]);
				}
				else if (strcmp(Curr_Command->command, "Add_APC") == 0) {
					Battlefield_Add_APC(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1],
						Curr_Command->command_args[2]);
				}
				else if (strcmp(Curr_Command->command, "Del_APC") == 0) {
					Battlefield_Delete_APC(pbattlefield, Curr_Command->command_args[0], Curr_Command->command_args[1],
						Curr_Command->command_args[2]);
				}
				else if (strcmp(Curr_Command->command, "Sold_Insert") == 0) {
					Battlefield_APC_Insert_Soldier(Curr_Command->command_args[0], Curr_Command->command_args[1],
						Curr_Command->command_args[2], Curr_Command->command_args[3], pbattlefield);
				}
				else if (strcmp(Curr_Command->command, "APC_Pop") == 0) {
					Battlefield_APC_Pop(Curr_Command->command_args[0], Curr_Command->command_args[1], 
						Curr_Command->command_args[2], pbattlefield);
				}
				else if (strcmp(Curr_Command->command, "Print") == 0) {
					Battlefield_Print(pbattlefield);
				}
				else {
					printf("Error: Illegal Command\n");
				}
				//moving to the next command
				List_Remove_Elem(Commands_List, &c);
				i++;
				itoa(i,c,10);
				Curr_Command = List_Get_Elem(Commands_List, &c);//need to check if index is initialized after exe
			}
		}
	}
	//Memory Clearance
	List_Delete(Commands_List);
	Command_Delete(Tmp_Command);
	if (Battlefield_Created = false) {
		return 0;
	}
	for (int i = 0; i < MAX_ARG; i++) {
		free(Command_Arguments[i]);
	}
	Battlefield_Delete(pbattlefield);
	return 0;

}
#pragma clang diagnostic pop

// :)










