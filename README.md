# minishell
42 project my own little bash.
Often called minihell, because of the manyfold edgecases need to be taken care of.
Try to break it - there already people who managed it by deleting folders they are currently in.

It handles correctly ’ (single quote) and " (double quote), also redirections <, >, << and >>.
Pipes are implemented and working, also $? and environment variables.
ctrl-C, ctrl-D and ctrl-\ are behaving correctly.

Following commands work:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

You need to have the readline library installed on your system.
