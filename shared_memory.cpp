// Compile command: g++ suconota_8812 -o suconota_8812.exe -lrt
// ./suconota_8812.exe prose.txt instruction.txt >> output.txt


#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string> 
#include <vector>

using namespace std;

int main(int argc, const char *argv[]) {

	// Check if we have the correct number of arguments

	if (argc != 3){
		write(STDERR_FILENO, "Wrong number of command line arguments\n", 36);
		return 1;
	}

	cout << "Parent Starting" << endl;
	
	// |Parent Child shm allocation|

	// pc will stand for parent child relation
	
	const int BUFFER_SIZE = 10;    // Number of elements in our array Buffer for Producer and Consumer

	const char *pcnameIntIn = "pcSHINTIN";
	int pcfdIn;

	if ( ( pcfdIn = shm_open(pcnameIntIn, O_CREAT | O_RDWR, 0666)) < 0) {

		cerr << "shm_open(pcnameIntIn, O_CREAT | O_RDWR, 0666) Failed" << endl;
		return 1;	
	}

	// Set the size of the shared memory for "pcSHINTIN".
	ftruncate(pcfdIn, sizeof(int));


	// Provide a memory address *pcptrIn for access to this shared memory object "pcSHINTIN".
	int *pcptrIn;

	if ( (pcptrIn = (int *)  mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, pcfdIn, 0)) < 0)
	{
		cerr << "pcptrIn = (int *)  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pcfdIn, 0) Failed" << endl;
		return 2;	
	}


	// Create the shared memory entity (object) for "pcSHINTOUT" and assign it an identifier.
	const char *pcnameIntOut = "pcSHINTOUT";
	int pcfdOut;
	if ( ( pcfdOut = shm_open(pcnameIntOut, O_CREAT | O_RDWR, 0666)) < 0) {

		cerr << "shm_open(pcnameIntOut, O_CREAT | O_RDWR, 0666) Failed" << endl;
		return 3;	
	}

	// Set the size of the shared memory for "pcSHINTOUT".
	ftruncate(pcfdOut, sizeof(int));


	// Provide a memory address *ptrOut for access to this shared memory object "pcSHINTOUT".
	int *pcptrOut;	
	if ( (pcptrOut = (int *)  mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, pcfdOut, 0)) < 0)
	{
		cerr << "pcptrOut = (int *)  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pcfdOut, 0) Failed" << endl;
		return 4;	
	}


	// Create the shared memory entity (object) for "pcSHINTBUFF" and assign it an identifier.
	const char *pcnameIntBuff = "pcSHINTBUFF";
	int pcfdBuff;

	if ( ( pcfdBuff = shm_open(pcnameIntBuff, O_CREAT | O_RDWR, 0666)) < 0) {

		cerr << "shm_open(pcnameIntBuff, O_CREAT | O_RDWR, 0666) Failed" << endl;
		return 5;	
	}

	// Set the size of the shared memory for "pcSHINTBUFF".
	ftruncate(pcfdBuff, BUFFER_SIZE * sizeof(int));


	/* Pointers to shared memory objects for pcshIntIn and pcshIntOut */
	char *pcptrBuff;

	if ( (pcptrBuff = (char *)  mmap(0, BUFFER_SIZE * sizeof(char[12]), PROT_READ | PROT_WRITE, MAP_SHARED, pcfdBuff, 0)) < 0)
	{
		cerr << "pcptrBuff = (int *)  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pcfdTBuff, 0) Failed" << endl;
		return 6;	
	}
	
	// Initialize the IN and OUT variables of the Producer Consumer algorithm.
	*pcptrIn = *pcptrOut = 0;
	
	// fork() creates a child process and returns a PID which is an integer that helps us identify our child process 
	pid_t child_pid = fork();
 
		
	if(child_pid < 0 ){ // Check if child process was created successfully
		write(STDERR_FILENO, "Can't fork the child process\n", 23);
		return 2;
											
	}else if(child_pid == 0){ // Child process code branch 
		cout << "Child Starting" << endl;
		// cg will stand for child grand child relation	
		const int cgBUFFER_SIZE = 10;    // Number of elements in our array Buffer for Producer and Consumer

		const char *cgnameIntIn = "cgSHINTIN";
		int cgfdIn;

		if ( ( cgfdIn = shm_open(cgnameIntIn, O_CREAT | O_RDWR, 0666)) < 0) {

			cerr << "shm_open(cgnameIntIn, O_CREAT | O_RDWR, 0666) Failed" << endl;
			return 1;	
		}

		// Set the size of the shared memory for "cgSHINTIN".
		ftruncate(cgfdIn, sizeof(int));


		// Provide a memory address *pcptrIn for access to this shared memory object "cgSHINTIN".
		int *cgptrIn;

		if ( (cgptrIn = (int *)  mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, cgfdIn, 0)) < 0)
		{
			cerr << "cgptrIn = (int *)  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, cgfdIn, 0) Failed" << endl;
			return 2;	
		}


		// Create the shared memory entity (object) for "cgSHINTOUT" and assign it an identifier.
		const char *cgnameIntOut = "cgSHINTOUT";
		int cgfdOut;
		if ( ( cgfdOut = shm_open(cgnameIntOut, O_CREAT | O_RDWR, 0666)) < 0) {

			cerr << "shm_open(cgnameIntOut, O_CREAT | O_RDWR, 0666) Failed" << endl;
			return 3;	
		}

		// Set the size of the shared memory for cgSHINTOUT".
		ftruncate(cgfdOut, sizeof(int));


		// Provide a memory address *cgptrOut for access to this shared memory object "cgSHINTOUT".
		int *cgptrOut;	
		if ( (cgptrOut = (int *)  mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, cgfdOut, 0)) < 0)
		{
			cerr << "cgptrOut = (int *)  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, cgfdOut, 0) Failed" << endl;
			return 4;	
		}


		// Create the shared memory entity (object) for "cgSHINTBUFF" and assign it an identifier.
		const char *cgnameIntBuff = "cgSHINTBUFF";
		int cgfdBuff;

		if ( ( cgfdBuff = shm_open(cgnameIntBuff, O_CREAT | O_RDWR, 0666)) < 0) {

			cerr << "shm_open(cgnameIntBuff, O_CREAT | O_RDWR, 0666) Failed" << endl;
			return 5;	
		}

		// Set the size of the shared memory for "cgSHINTBUFF".
		ftruncate(cgfdBuff, BUFFER_SIZE * sizeof(int));


		// Pointers to shared memory objects for cgshIntIn and cgshIntOut 
		char *cgptrBuff;

		if ( (cgptrBuff = (char *)  mmap(0, BUFFER_SIZE * sizeof(char[14]), PROT_READ | PROT_WRITE, MAP_SHARED, cgfdBuff, 0)) < 0)
		{
			cerr << "cgptrBuff = (int *)  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, cgfdTBuff, 0) Failed" << endl;
			return 6;	
		}
	
		// Initialize the IN and OUT variables of the Producer Consumer algorithm.
		*cgptrIn = *cgptrOut = 0;	
	
		//  Create Grand Child
		pid_t grandchild_pid = fork();
 
		
		if(grandchild_pid < 0 ){ // Check if grandchild process was created successfully
			write(STDERR_FILENO, "Can't fork the grandchild process\n", 23);
			return 2;
											
		}else if(grandchild_pid == 0){ // Grandchild process code branch 
			cout << "Grandchild Starting" << endl;
			int b = 0;
			while (1) {
				while (*cgptrIn == *cgptrOut); // wait till child sends something 
				int c = 0;
				
				// The size of each message block is 14 with '*' as a sentinel value
				cout << "Grandchild receive: \"";
				while(*(cgptrBuff + (*cgptrOut *14 + c)) != '*'){
					cout << *(cgptrBuff + (*cgptrOut *14 + c))  ;
					c++;
				}
				cout << "\""<< endl;
				*cgptrOut = ( (*cgptrOut) + 1) % cgBUFFER_SIZE;
				if (b++ == 19) break; // Break after reading all messages
			}
			cout << "Grandchild Terminating" << endl;
		
			return 0;
		}
		else {																																																																																																																										
		// Child Reading Input 	
			int b = 0;
			int f_read = open(argv[2], O_RDONLY); //Reads Prose file
			while (1) {
				while (*pcptrIn == *pcptrOut); // wait till parent sends something
				//char next_consumed = *(pcptrBuff + (*pcptrOut *12));    
		
				int c = 0;
				string number = "";
		
				// The size of each message block is 12 with 'x' as a sentinel value
				vector <int> g1;
				while(*(pcptrBuff + (*pcptrOut *12 + c)) != 'x'){
					if( !(   int(*(pcptrBuff + (*pcptrOut*12 + c))) > 47 && int(*(pcptrBuff + (*pcptrOut *12 + c))) < 58)){
						g1.push_back(stoi(number));
						number = "";
						c++;
					} else{
						number += *(pcptrBuff + ((*pcptrOut *12) + c));
						c++;
					}
				}
				g1.push_back(stoi(number));
				cout << "Child recives: " << g1[0] << ", "<< g1[1] << ", " << g1[2]<< " from Parent" << endl;
			
				// Grand Child Read and sent read txt from prose file
				
				// g1[0] = i = position ,0 = beginning, 1 = current, 2 = end
				// g1[1] = j = offset
				// g1[2] = k = length
				
				char buffer[g1[2]];
				lseek(f_read,g1[1],g1[0]);
				read(f_read, buffer, g1[2]);
						
				//string str 
				cout << "Child: Exec: " << g1[0] << ", "<< g1[1] << ", " << g1[2] << " \"";
				for(char a: buffer){
					cout << a;
				}
				cout << " \""<<  endl;
				
				while( ( (*(cgptrIn) + 1 ) % cgBUFFER_SIZE) == *cgptrOut);
				cout << "Child: Sent \"";
				int l = 0;
				for(char a: buffer){
					*(cgptrBuff + ((*cgptrIn) *14 + l)) = a;
					l++;
					cout << a;
				}
				cout << " \" To Grand Child" << endl;
				*(cgptrBuff + ((*cgptrIn) *14 + l)) = '*' ;
	 			*cgptrIn = (*cgptrIn + 1) % BUFFER_SIZE;
				
				
				*pcptrOut = ( (*pcptrOut) + 1) % BUFFER_SIZE;
				if (b++ == 19) break; // Break after reading all messages
			}
			
			
			int status;

        	// Wait(block) for child to terminate.
        	if (wait(&status) == grandchild_pid)  {   

       			 // Program terminated normally (it didin't crash nor was aborted though it may have failed ).
        		if  (WIFEXITED(status)) {    
            		wcout << "Child: Grandchild normal termination" << endl;
            		int childstat = WEXITSTATUS(status);
		        	cout << "Child: Grandchild exit status is " << childstat << endl;   // Better way to do this?
            	} 
            		// Program terminated abnormally.
            	else if (WIFSIGNALED(status))  {
		    		cerr << "Child: Grandchild abnormal termination" << endl ;
            	}  
        	 }   
        	else {   // wait() call failed by parent process.
	     		cerr << "Parent: wait() call failed" << endl ;  
         	}

	     	// Remove the shared memory objects.
	     	shm_unlink(cgnameIntIn);
	     	shm_unlink(cgnameIntOut);
	    	shm_unlink(cgnameIntBuff);
				
			cout << "Child Terminating" << endl;
			return 0;
		}																	
																			
	} else{
	
		const int SIZ = 10;
		int f1; 
		// Check if we can access the source file
	
		if((f1 = open(argv[1], O_RDONLY, 0)) == -1){
			write(STDOUT_FILENO, "Can't open input file\n",28);
			return 0;
		}
	
		char buf[SIZ];
		int n;
		vector<string> input;
		int r = 0;
		string line = "";
		// Algorith to read the instructions file
		while((n = read(f1, buf, SIZ)) > 0){
			r = 0;
			while(r < sizeof(buf)){
				if(buf[r] == '\n' )
				{
					input.push_back(line);
					line = "";
					r++;
				} 
				else 
				{
					// I purposefully put 'o' after reading a char because my buffer would maintain portions of previously read input
					// and this was a problem. Inorder to prevent this I checked if buf[r] == 'o' and if so I stop reading;
					if(buf[r] == 'o')
					{
				 		input.push_back(line);
				 		break;
					}
					else
					{
						line += buf[r];
						buf[r] = 'o'; 
						r++;
					}
				}
			}
		}	
		input.push_back(line);
	
		
		int next_produced = 0;   // Parent's private variable that child doesn't see.

		//string passed = "";
		while (1) {
 	
 			while( ( (*(pcptrIn) + 1 ) % BUFFER_SIZE) == *pcptrOut);
 				int x = 0;
 				cout << "Parent: Sent ";
 				while( x < input[next_produced].size()){ 
 					*(pcptrBuff + ((*pcptrIn) *12 + x)) = input[next_produced][x];
 						cout << *(pcptrBuff + ((*pcptrIn) *12 + x));
 					x++;
 				}
 				cout << " to Child" << endl;
 				// Sentinel value ('x') to end of message 
 				*(pcptrBuff + ((*pcptrIn) *12 + x)) = 'x' ;
	 			*pcptrIn = (*pcptrIn + 1) % BUFFER_SIZE;

                // We break from this loop after a number of iterations, . 
				if (next_produced++ == 19) break; 
        } 

        int status;

        // Wait(block) for child to terminate.
        if (wait(&status) == child_pid)  {   

        // Program terminated normally (it didin't crash nor was aborted though it may have failed ).
        	if  (WIFEXITED(status)) {    
            	wcout << "Parent: Child normal termination" << endl;
            	int childstat = WEXITSTATUS(status);
		        cout << "Parent: Child exit status is " << childstat << endl;   // Better way to do this?
            } 
            // Program terminated abnormally.
            else if (WIFSIGNALED(status))  {
		    	cerr << "Parent: Child abnormal termination" << endl ;
            }  
         }   
         else {   // wait() call failed by parent process.
	     		cerr << "Parent: wait() call failed" << endl ;  
         }
	     
	     // Remove the shared memory objects.
	     shm_unlink(pcnameIntIn);
	     shm_unlink(pcnameIntOut);
	     shm_unlink(pcnameIntBuff);

	     cout << "Parent: Terminating " << endl;
	     return 0;	
	}
}
