#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;
void print_ala();
void print_mdt();
void print_mnt();
void print_out();
void print_in();
void print_final();
void pass1();
void pass2();
fstream INPUT,ALA,MNT,MDT,OUTPUT,FINAL;

int main()
{
	pass1();
	cout<<"\tThe input taken is:"<<endl<<endl;
	print_in();
	int ch;
		do
	{
		cout<<"\tMain Menu"<<endl;
		cout<<"\t1: Print ALA table\n\t2: Print MNT\n\t3: Print MDT\n\t4: Print Output table for Pass 1\n\t5: Print Output Table for Pass 2\n\t6: Exit\n\t";
		cout<<"\tEnter your choice:";
		cin>>ch;
		cout<<endl;
		switch(ch)
		{
			case 1: print_ala();
			        break;
			case 2: print_mnt();
			        break;
			case 3: print_mdt();
			        break;
			case 4: print_out();
			        break;
			case 5: print_final();
			        break;
			case 6:	exit(0);
			default:cout<<"\tWrong Choice! Please choose again!"<<endl;
		}
	}while(ch!=6);
	return 0;
}

void print_ala()
{
    string argument;
	ALA.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\ala.txt",std::ios::in);
	cout<<"\t----------ALA----------"<<endl;
	while(getline(ALA,argument))
    {
    	string arg1,arg2;
	    if(ALA.eof())
	    	break;
	    ALA>>arg1>>arg2;
	    cout<<"\t"<<arg1<<endl;
        cout<<"\t"<<arg2<<endl;
    }
    cout<<"\t----------------------------------\n\n";
    ALA.close();
}

void print_mdt()
{
    string content;
	MDT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\mdt.txt",std::ios::in);
	cout<<"\t---------Macro Definition Table---------"<<endl;
	while(getline(MDT,content))
    {
    	string mdtc,def,arg;
	    if(MDT.eof())
	    	break;
	    MDT>>mdtc>>def>>arg;
	    if(arg==".")
	        cout<<"\t"<<mdtc<<"\t"<<def<<endl;
	    else
	        cout<<"\t"<<mdtc<<"\t"<<def<<"\t"<<arg<<endl;
    }
     cout<<"\t----------------------------------\n\n";
    MDT.close();
}

void print_mnt()
{
    string content;
	MNT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\mnt.txt",std::ios::in);
	cout<<"\t---------Macro Name Table---------"<<endl;
	while(getline(MNT,content))
    {
    	string mntc,name,arg,mdtp;
	    if(MNT.eof())
	    	break;
	    MNT>>mntc>>name>>arg>>mdtp;
	    cout<<"\t"<<mntc<<"\t"<<name<<"\t"<<arg<<"\t"<<mdtp<<endl;
    }
     cout<<"\t----------------------------------\n\n";
    MNT.close();
}

void print_out()
{
string content;
	OUTPUT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\output.txt",std::ios::in);
	cout<<endl<<"\t---------Output Table---------"<<endl;
	while(getline(OUTPUT,content))
    {
    	string def,arg;
	    if(OUTPUT.eof())
	    	break;
	    OUTPUT>>def>>arg;
	    if(arg==".")
	        cout<<"\t\t"<<def<<endl;
	    else
	        cout<<"\t\t"<<def<<"\t"<<arg<<endl;
    }
    cout<<"\t------------------------------\n\n";
    OUTPUT.close();	
}

void print_in()
{
	string content;
	INPUT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\input.txt",std::ios::in);
	cout<<endl<<"\t---------Input Macro Table---------"<<endl;
	while(getline(INPUT,content))
    {
    	string def,arg;
	    if(INPUT.eof())
	    	break;
	    INPUT>>def>>arg;
	    if(arg==".")
	        cout<<"\t\t"<<def<<endl;
	    else
	        cout<<"\t\t"<<def<<"\t"<<arg<<endl;
    }
    cout<<"\t-----------------------------------\n\n";
    INPUT.close();
}

void pass1()
{
	
	string content;
	int cn=1,cd=1;          // set mdtc and mntc to 1
	// opening files for execution
	INPUT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\input.txt",std::ios::in);
	MNT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\mnt.txt",std::ios::out | std::ios::in);
	MDT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\mdt.txt",std::ios::out | std::ios::in);
	OUTPUT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\output.txt",std::ios::out | std::ios::in);
	
	MNT<<endl;
	MDT<<endl;
	OUTPUT<<endl;
	while(getline(INPUT,content))        //reading source card 
    {
    	string ip1,ip2;
	    if(INPUT.eof())                 // for ending the loop once file is finished reading
	    	break;
	    INPUT>>ip1>>ip2;                //reading input file into ip1 and ip2
	    if(ip1=="MACRO")                //execute if macro keyword is found
	    {
	    	getline(INPUT,content);     // read next source card
	    	INPUT>>ip1>>ip2;
	    	// entering macro name and mntc into macro name table
	    	MNT<<cn<<"\t"<<ip1<<"\t"<<ip2<<"\t"<<cd<<endl;
	    	cn++;                      // increment mntc counter
	    	
	    	//prepare argument list array
	    	string arg1=ip2.substr(0,2);
	    	string arg2=ip2.substr(3,2);
	    	ALA.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\ala.txt",std::ios::out | std::ios::in| std::ios::trunc);
	    	ALA<<endl<<arg1<<"\t"<<arg2<<endl;
	    	
	    	//entering macro name card into mdtc
	    	MDT<<cd<<"\t"<<ip1<<"\t"<<ip2<<endl;
	    	cd++;                     // increment mdtc counter
	    	
	    	while(getline(INPUT,content))           //read next source card
            {
            	INPUT>>ip1>>ip2;
	            if(ip1!="MEND")                    // operations until MACRO ends
	            {
	            	if(ip2.substr(2,2)==arg1)
	            	    ip2="#0";
	            	else
	            	    ip2="#1";
	            	MDT<<cd<<"\t"<<ip1<<"\t"<<ip2<<endl;
				}
	    	    else                             // when "MEND" is found
	    	    {
	    	    	MDT<<cd<<"\t"<<ip1<<"\t"<<ip2<<endl;
	    	    	cd++;
	    	    	break;
				}
	    	    cd++;                            //increment mdtc counter
            }
		}
		else
			OUTPUT<<ip1<<"\t"<<ip2<<endl;        //copying source card
		ALA.close();                          // closing argument table
    }
    //incrementing mdtc and mntc counters
    MDT<<cd<<endl;
    MNT<<cn<<endl;
    
    //closing all files
    MNT.close();
    MDT.close();
    INPUT.close();
    OUTPUT.close();
    //pass 1 ends executed
    //calling pass 2
    pass2();
}
void pass2()
{
	string conout,conname,condef;
	OUTPUT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\output.txt",std::ios::out | std::ios::in);
	FINAL.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\final.txt",std::ios::out | std::ios::in);
	
	
	FINAL<<endl;
	while(getline(OUTPUT,conout))        //reading source card passed by pass1
	{
		if(OUTPUT.eof())                  // checking end of file
		    break;
		string ip1,ip2;
		OUTPUT>>ip1>>ip2;
		MNT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\mnt.txt",std::ios::out | std::ios::in);
		int c=0;                          //as a counter for checking when MACRO is not found
		while(getline(MNT,conname))   //read source card of mnt
		{
			string name1,name2,name3,name4;
			MNT>>name1>>name2>>name3>>name4;
			
			if(MNT.eof())
			{
				if(c==0)                     //traversed entire mnt
				    FINAL<<ip1<<"\t"<<ip2<<endl;
				break;
			}				
			else if(ip1!=name2)                    //checking if name does not match in mnt table
				continue;  
			else                              // if name is found in mnt table
			{
				c++;                        // stating that we found a MACRO
				stringstream deftabpointer(name4);
				int mdtp=0;                   // the pointer mdtp points to index in mdt
				deftabpointer>>mdtp;
				
				ALA.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\ala.txt",std::ios::out | std::ios::in | std::ios::trunc);
				string arg1=ip2.substr(0,1);  // extracting 1st argument from 2nd part of input of OUTPUT file
				string arg2=ip2.substr(2,1);  // extracting 2nd argument from 2nd part of input of OUTPUT file
				ALA<<endl<<arg1<<"\t"<<arg2;     // setting up ALA
				
				MDT.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\mdt.txt",std::ios::out | std::ios::in);
				while(getline(MDT,condef))  // extracting lines from mdt
				{
					if(MDT.eof())
					    break;
					
					string in,def,para;
					MDT>>in>>def>>para;
					
					stringstream indexmdt(in);       //converting index into a integer
					int index=0;
					indexmdt>>index;
					if(mdtp!=index)      // checking if mdtp is pointing to the index position that is required
					    continue;
					else
					{
						getline(MDT,condef);
						MDT>>index>>def>>para;
						mdtp++;                  // incrementing mdt pointer
						while(def!="MEND")            // until we find MEND
					    {
						    
					    	if(para=="#0")       // if parameter is indexed 0 then 1st argument is passed
					    	    FINAL<<def<<"\t"<<arg1<<endl;
					    	else                   // if parameter is indexed 1 then 2nd argument is passed
					    	    FINAL<<def<<"\t"<<arg2<<endl;
					    	getline(MDT,condef);
						    MDT>>index>>def>>para;
						    mdtp++;                  // incrementing mdt pointer
					    }
					    break;
					}	
				}
				MDT.close();
			}
			ALA.close();
		}
		MNT.close();
	}
	
	OUTPUT.close();
	FINAL.close();
}

void print_final()
{
	string content;
	FINAL.open("C:\\Users\\archi\\OneDrive\\Documents\\SP\\final.txt",std::ios::in);
	cout<<endl<<"\t---------Final Macro Table---------"<<endl;
	while(getline(FINAL,content))
    {
    	string def,arg;
	    if(FINAL.eof())
	    	break;
	    FINAL>>def>>arg;
	    if(arg==".")
	        cout<<"\t\t"<<def<<endl;
	    else
	        cout<<"\t\t"<<def<<"\t"<<arg<<endl;
    }
    cout<<"\t-----------------------------------\n\n";
    FINAL.close();
}
