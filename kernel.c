void printString(char*);
void readString(char*);
void readSector(char*, int);
void readFile(char*, char*);
void executeProgram(char*, int);
void terminate();
void writeSector(char*, int);
void deleteFile(char*);
void writeFile(char*, char*, int);
void printChar(char);
int mod(int, int);
int div(int, int);
void handleInterrupt21(int, int, int, int);



main(){
	
	char buffer[13312];
	

	makeInterrupt21();

	interrupt(0x21, 4, "shell\0", 0x2000, 0);


	
	

	while(1);

	return 0;
			
	
}

void printChar(char l) 
{ 
	interrupt(0x10, 0xe * 256 + l , 0, 0, 0); 
}

void readFile(char* fileName, char* buffer)
{
	
	int i, n;
	char dir[512];	

	readSector(dir,2);
	
	for ( i=0 ; i<16; i++)
	{
		for (n=0; n<6 ;n++)
		{
		   if ( dir[n+32*i]!=fileName[n])

		 break;	
		}
		if(n==6)

		 break;
	}

		if (n==6)
		{
			while(n<32)
			{

				if( dir[n+32*i]!=0x00)
				{
					readSector(buffer+512*(n-6),dir[n+32*i]);
				}
				n++;
			}
	
	}

	if(i==16)
	{

		printString("error: file not found !!");

	}	
}	

void executeProgram(char* name, int segment)
{
	int i;
	char readBuffer[13312];

	printString("Loading Program...\n");
	readFile(name,readBuffer);

		for( i=0; i <13312; i++){
		putInMemory(segment, i, readBuffer[i]);
		}
	
		
	launchProgram(segment);
}	

void terminate()
{

	char shell[6];
	shell[0] = "s";
	shell[1] = "h";
	shell[2] = "e";
	shell[3] = "l";
	shell[4] = "l";
	interrupt(0x21,4,"shell\0",0x2000,0);	
}

void writeSector(char* buffer, int sector)
{
	
	int CH = sector/36;
	int CL = mod (sector, 18);
	int DH = mod (sector/18,2);
	interrupt (0x13, 3*256+1, buffer, CH*256+CL+1, DH*256+0);

}

void deleteFile(char* file)
{	

	char dir[512], map[512];
	int i , n, j, p ; 
	int count = 0;
	int index; 
	int sectorcount = 0;


	// load the dir and map to 512 char array
	readSector(map,1);
	readSector(dir,2);

	// search thro the dir 
	for (i=0; i <32;i++)
	{
		count++;       // to figure out which file entery is the file located 
		for(n=0; n<6; n++)
		{

			if (dir[i*32+n] == file[n])
			{

				dir[i*32+n] = 0x00;  // set the first byte to 0x00
			}
		}
	}

	index = count*32+6;  // set the index to where the file is located 

	for(j=0; j<26;j++)
	{     // to run thro the sectors of the file 
		while ( dir[index+j] != 0x00)
		{
			sectorcount ++;   // to count how many sectors is the file using 
		}

	} 

	for ( p=0; p < sectorcount; p++)
	{

		map[p]= 0x00;  // set the coursponding map to 0x00
	}

	writeSector(map,1);
	writeSector(dir,2);

}	

void writeFile(char* name, char* content, int number)
{	
	//The function should be called with a character array holding the file name, 
	//a character array holding the file contents, 
	//and the number of sectors to be written to the disk.

	char dir[512];
	char map[512];
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	int m=0;
	int dirindex;

	
	readSector(dir,2);
	readSector(map,1);


	for(i=0;i<16;i++)
	{
		if(dir[i*32] == 0x00)
		{
			
			for(j=0;j<6;j++)
			{
				dir[(i*32)+j] = name[j];
			}
			break;
			
		}
		
	}

	
	
	

	for(k=0;k<number;k++)
	{
		for(l=0;l<256;l++)
		{
			if(map[l] == 0x00)
			{
				break;
			}
		}
		
		map[l] = 0xFF;
		dir[(i*32)+(j+k)] = l;
		writeSector(content, l);
		
	}






	writeSector(map,1);
	writeSector(dir,2);





	
}
	

	
		//4. For each sector making up the file:
		//Find a free sector by searching through the Map for a 0x00
 		//Set that sector to 0xFF in the Map
 		//Add that sector number to the file's directory entry
 		//Write 512 bytes from the buffer holding the file to that sector




void printString(char* chars) 
{ 
	int i; 
	int al; 
	int ah; 

	i = 0; 
	while(chars[i] != '\0') 
	{ 
		interrupt(0x10, 0xe *256 + chars[i],0,0,0); 
		i++; 
	} 
}

//void readString(char* array){
	//int i=0;
	//char a;
	//char b;
	
//	while(b != 0xd){	
							/*while b is not enter*/
	//	a = interrupt(0x16,0,0,0,0);
	//	array[i] = a;
	//	if(a == 0x8){
			
	//		array[i] = 0;
	//		if(i>0){
	//			i--;
	//			interrupt(0x10,(0xe*256)+0x8,0,0,0);
	//			interrupt(0x10,(0xe*256)+' ',0,0,0);
	//			array[i]=' ';

				
	//		}
	//	}
	//	b = array[i];
	//	interrupt(0x10,(0xe*256)+a,0,0,0);
	//	i++;
		
	
//	}
	
//	array[i] = '\n';
//	array[i+1] = 0x0;
//	array[i+2] = 0xa;
	
	
	
//}

void readString(char* chars) 
{ 
	int i = 0; 
	char l; 
	while((l = interrupt(0x16, 0, 0, 0, 0)) != 0xd)
	{ 
		if( 0x8 == l)
		{ 
			chars[i] = 0; 
			if (i > 0)
			{ 
				i--; 
				printChar(0x8); 
				printChar(' '); 
				printChar(0x8); 
			} 
		} 
		else 
		{ 
			chars[i] = l; 
			i++; 
			printChar(l); 
		} 
	}
}
/*
void readString(char* chars)
{
	int i = 0;	
	char ch = interrupt(0x16,0,0,0,0);
	
	while(ch != 0xd)
	{
		chars[i] = ch;	
		interrupt(0x10,0xe*256+ch,0,0,0);
		i ++;
		ch = interrupt(0x16,0,0,0,0);



		while ( ch == 0x8)
		{
			if ( i > 0 )
			{
			i --;
			
			}
		ch = interrupt(0x16,0,0,0,0);
		} 
	}
		
	chars[i]= '\n';
	chars[i+1]= 0x0;	
	chars[i+2]=0xa;			
}
*/

void readSector(char* buffer, int sector)
{
	
	int CH = sector/36;
	int CL = mod (sector, 18);
	int DH = mod (sector/18,2);
	interrupt (0x13, 2*256+1, buffer, CH*256+CL+1, DH*256+0);

}


int mod(int a, int b){
	while(a >= b){
		a = a-b;
	}

	return a;

}

int div(int a, int b){
	int q;
	while(q*b <= a){
		q=q+1;
	}
	return q-1;

}


void handleInterrupt21(int ax, int bx, int cx, int dx)
{

	//printString(" If this prints, it means I'm almost done with project B \n\0");

	if (ax == 0)
	{
	printString(bx);
	}

	else if ( ax == 1)
	{
	readString(bx);
	}

	else if (ax == 2)
	{
	readSector(bx, cx);
	}

	else if ( ax == 3)
	{
	readFile(bx,cx);
	}

	else if (ax == 4)
	{
	executeProgram(bx,cx);
	}

	else if (ax == 5)	
	{
	terminate();
	}

	else if (ax == 6)
	{
	writeSector(bx,cx);
	}

	else if (ax == 7)
	{
	deleteFile(bx);
	}
	else if (ax == 8)
	{
	writeFile(bx, cx, dx); 
	}


}
