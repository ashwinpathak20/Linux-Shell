1.)Details Of Implementation:
	a.) ; separated commands
	b.) & to run a process background
	c.) A shell prompt of the form:
			<username@system_name:curr_dir>
			Here, the path is relative
	d.) Some built in commands like cd,pwd and echo
	e.) Some commands like ls,ps,etc:
	f.) quit to stop the shell
	g.) foreground and background implementation
	h.) printing message if the background process exits
	i.) built in pinfo command to print:
			pid,process status,memory,executable path
	j.) redirection of the file 
	k.) multiple piping functionality
	l.) integration of piping and redirection
	m.) foreground option
	n.) jobs to list the processes in background
	o.) kjob to handle the signal
	p.) kill to kill all background processes
	q.) cntrl-C to terminate a command
	r.) cntrl-D to exit the shell
	s.) cntrl-Z to stop a process and run it in background

2.)Decisions I made:
	a.) No flags implementation in built in commands
	b.) Limited characters for some arguments (not all)
	c.) Redirection commands are space separated

3.)As follows:
	a.)os.c: Main implmentation of the shell like scanning the commands and calling all the functions.
	b.)cd.c: To change the directory
	c.)echo.c: To echo the arguments
	d.)execute.c: To ececute the commands using fork - execvp commands ,fg , redirection,cntrl-C,cntrl-D
	e.)pwd.c: To return the present working directory
	f.)read_line.c:To read the arguments
	g.)token1.c: To tokenize the arguments using strtok
	h.)signal.c: To print message if background process exits,cntrl-Z
	i.)pinfo.c: To implement the built in command pinfo
	h.)function.h: Header file
	i.)Makefile
	j.)jobs.c: To list all background jobs
	k.)killallbg.c: To kill all background processes
	l.)kjobs.c: To handle signal for a particular job ID
	m.)piping.c: To implement pipe functionality


4.)To compile and run:
	a.)To compile: make
	b.)To run:./a.out
