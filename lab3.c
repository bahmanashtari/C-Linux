{
    "version": "0.2.0",
    "configurations": [{
            "name": "C++ Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}/lab3.c",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceRoot}",
            "environment": [],
            "externalConsole": true,
            "linux": {
                "MIMode": "gdb"
            },
            "osx": {
                "MIMode": "lldb"
            },
            "windows": {
                "MIMode": "gdb"
            }
        },
        {
            "name": "C++ Attach",
            "type": "cppdbg",
            "request": "attach",
            "program": "${workspaceRoot}/a.out",
            "processId": "${command.pickProcess}",
            "linux": {
                "MIMode": "gdb"
            },
            "osx": {
                "MIMode": "lldb"
            },
            "windows": {
                "MIMode": "gdb"
            }
        }
    ]
}{
		printf("Error/unable to open the input file: %s", FILE_IN);
		exit(EXIT_FAILURE);
	}

	out_f_ptr = fopen(FILE_OUT, "w");	//open the file to write into it
	if(out_f_ptr == NULL)
	{
		printf("Error/unable to open the output file: %s", FILE_OUT);
		exit(EXIT_FAILURE);
	}

	printHeader(out_f_ptr);
	topAreaAndVolume(in_f_ptr, out_f_ptr);
	fclose(in_f_ptr);
	fclose(out_f_ptr);	

	return EXIT_SUCCESS;
}

//Functions

void printHeader(FILE * f_out)
{
	
	fprintf(f_out, "  Bahman Ashtari, Lab3, Section2\n");
	fprintf(f_out, "  Radius     Height     Top Area      Volume \n");
	fprintf(f_out, " --------   --------  ------------  ----------\n");
}

void topAreaAndVolume(FILE * f_in, FILE * f_out)
{
	double r, h;		//r for radios, h for height
	while((fscanf(f_in, "%lf %lf\n", &r, &h)) == 2)
	{
		double area =  (M_PI*r*r);
		double volume = (M_PI*r*r*h);
		fprintf(f_out, "%7.3lf   %9.3lf %12.3lf    %10.3lf\n", r, h, area, volume);
	}  		
}
