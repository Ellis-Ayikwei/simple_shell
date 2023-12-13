#include "shell.h"

/**
 * _shexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _shexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _shcd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _shcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _shhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _shelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
_puts("Simple Shell Help Menu:\n");
    _puts("  help        Display this help menu\n");
    _puts("  cd          Change current directory\n");
    _puts("  exit        Exit the shell\n");
    _puts("  env         Display the environment variables\n");
    _puts("  history     Display command history\n");
    _puts("  alias       Display or set command aliases\n");
    _puts("  setenv      Set environment variables\n");
    _puts("  unsetenv    Unset environment variables\n");

    _puts("\nCommand Details:\n");
    _puts("  help        - Display information about available commands\n");
    _puts("  cd          - Change current directory. Usage: cd [directory]\n");
    _puts("  exit        - Exit the shell. Usage: exit [status]\n");
    _puts("  env         - Display environment variables\n");
    _puts("  history     - Display command history\n");
    _puts("  alias       - Display or set command aliases\n");
    _puts("  setenv      - Set environment variables. Usage: setenv VARIABLE VALUE\n");
    _puts("  unsetenv    - Unset environment variables. Usage: unsetenv VARIABLE\n");	
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

