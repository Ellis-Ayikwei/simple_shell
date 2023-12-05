#ifndef _SHELL_H_
#define _SHELL_H_


void display_prompt();
char** read_command();
void execute_command(char** command);


#endif /* _SHELL_H_ */
