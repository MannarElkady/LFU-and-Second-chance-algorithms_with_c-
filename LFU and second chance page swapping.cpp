#include<iostream>
#include <stdlib.h>     //library of random number
using namespace std;
//Frames = 3 .. random sequence generator

#define numFrames 3
int numOfPages;
int *seq; // seq = array of pages
int frames[numFrames]; //data in frames
int pgfaultcnt=0;
//int seq[20]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
void generateData()
{
	int seed;
	cout<<"Enter the seed number ";
	cin>>seed;
	srand(seed);
	cout <<"\nEnter length of page reference sequence:";
    cin>> numOfPages;
    seq=new int [numOfPages];
    cout<<"\nGenerating data...\n";
    cout<<"The sequence is ";
    for(int i=0; i<numOfPages; i++) 
	{
		seq[i]=rand() % 8;
		cout<<seq[i]<<"\t";
	}
	cout<<"\n";	
	/*
	for (int i=0; i<numOfPages;i++)
	{
		cin>>seq[i];
		cout <<"\t";
	}
	cout<<"\n";
	*/
}
void initialize()
{
    pgfaultcnt=0;
    for(int i=0; i<numFrames; i++)  frames[i]=9999;
}
bool isinFrames(int data)  // bta5od rkm (page) w tshofo mwgod fl frames wla l2 
{ 
    for(int i=0; i<numFrames; i++)
    {
        if(frames[i]==data)
        {
        	return true;
        }
 
    }
 
    return false;
}
int getPgIndexInFrame(int data) // bdeha qymt el page btrg3li el index bt3t el page fl frame w bst5dmha b3d ma ashof el rrkm bt3 elpage already mwgod fl frame wla l2 34an azwd elcounter 
// w kman ashof hal hytl3li page fault wla l2
{
    int pageIndex;
    for(int k=0; k<numFrames; k++)
    {
        if(frames[k]==data)
        {
            pageIndex=k;
            break;
        }
    }
    return pageIndex;
}
void dispPages()
{
    for (int k=0; k<numFrames; k++)
    {
        if(frames[k]!=9999)
        	{
        	//	cout<<"--------";
            	cout<<frames[k]<<"\t";
			}
			
         //   cout<<frames[k]<<"\n";
       // 	cout<<"--------";

    }
    cout<<"\n";
 
}
 
void dispPgFaultCnt()
{
    cout<<"\nTotal no of page faults: "<<pgfaultcnt<<"\n";
}

void lfu() // least frequently used
{
    int usedcnt[numFrames];         // counter array for numbers used in frames 
    int least,repin,sofarcnt=0,emptyIndexFrame=0; //least= least counter number (in counter array of frames) used , repin= b7ot feh el index bt3 a2l page etqrrt fl frame ele hbdl mkano
	//, sofarcnt=  ,emptyIndexFrame= index of last empty frame
    initialize(); //hysfr el pgsfault counter
    for(int i=0; i<numFrames; i++) //hysfr el counter fl2wl bs bt3 el used 
        usedcnt[i]=0;
    for(int i=0; i<numOfPages; i++)
    {
        if(isinFrames(seq[i])) // lw elrkm bt3 el page already mwgod fl frame byzwd el counter bt3 el used w mfysh page fault
        {
            int pageIndex=getPgIndexInFrame(seq[i]);
            usedcnt[pageIndex]++;
            cout<<"No page fault! \n";
        }
        else // lw elrkm bt3 elpage msh mwgod (fe 7altyen lda)
        {
            pgfaultcnt++;    //bzwd el page faults counter 3lshan el rkm msh mwgood feh el frames w hyro7 ygyebo mn elmemory
            if(emptyIndexFrame<numFrames) //lw elframes lsa kolha mtmltsh w lsa f mkan fadi fl frames bd5l feh w azwd el frame emtpy index b 1 
            {
                frames[emptyIndexFrame]=seq[i];
                usedcnt[emptyIndexFrame]=usedcnt[emptyIndexFrame]+1;
                emptyIndexFrame++;
            }
            else //lw el frames kolha mliana w msh fdya  
            {
                least=9999;
                int counter=0;
                int temp[numFrames]={9999,9999,9999}; //initialize 9999 means it holds nothing
                bool found=false;
                for(int k=0; k<numFrames; k++)   // h3dy 3ala el gwa el frames w fydtha eno yshof anye a2l page etkrrt w mmkn ashylha aw lw 3ndi aktr mn wa7d yzwdlli elcounter w y5znha
				{
                    if(usedcnt[k]<least)   // kol rakm gwa leh counter bta3o w  bydwr 3la a2l qymt counter ll frames de b2ni afdl a7ot a2l qymt tqrar ll2rkam ele fl frames b7otha f least
                    {
                    	//hna msh bysgl el  a awl least(fltkrar) count bs
                        least=usedcnt[k]; 
                        repin=k; // el k de el index bt3 elrkm el least frequently used ele hbdl fmkano
                    }
                    if(usedcnt[k]==least)  // lw elcounter bt3 el least b2a f counter tany bnfs qymto (y3ni f etnin least aw aktr)  //lw l2a counter tany
					{
					temp[counter]=k;   // temp de shyla el index bt3 el frame ele elcounting bt3ha mtswaii 
					counter++;
					}
                }
                if(counter>1)   // lw aktr mn rkm feh el frame mtsween feh el least frequently used 
                    {                   	
                    	for(int m=i-1; m>=0;m--)     // b3mel loop 3ala el seuqence mn el page sequence ele 3yza ad5lha -1  l5yet el2wl w bynzl mn el25r ll2wl
						{
							for(int z=0;z<numFrames;z++)     //loop 3la el2rkam lmtswia mn7ys elcounter fl frames (loop 3ltemp)
							{
								if(temp[z]!=9999) //y3ni yshof w y3di 3l condiition de f ay frame ela ele mtkrr kter w leyeh qyma fl temp bltkrar da 
								{
									if(seq[m]==frames[temp[z]]) // byqarn el 
									{
	
										counter--; // byminus kol ma2 el condidtion yt722 w
										if(counter==0) //elcounter hyb2a b zero lma 
										{
											found=true;
											repin=temp[z];
										}
										temp[z]=9999; //bfdl wna rg3a mn el25r ll2wl ams7 elpages ele a2blha odam w arg3 ll22dm wra
									}
								}
								if(found) break; //shrt el5rog mn el loop eele fo2yha
							}
							if(found) break;
						}
					}
                frames[repin]=seq[i]; //b7ot elrkm(page) bt3i elgded fl frame ele feha elpage ele etkrrt a2l w7da  w de 7tt ELSWAPPING 
                sofarcnt=0; //counter byshof el page(elrkm) etkrt kam mra mn el2wl 5als l7d elpoint bt3ti ele ana feha de w 7ta b3d ma tl3t mn elframes abl kda
                for(int k=0; k<=i; k++) 
                {
					if(seq[i]==seq[k])  sofarcnt=sofarcnt+1; // el counter byzyed lw l2a nfs qymt elframe ele wa2f 3leha w byshofha etkrrt kam mra 
            	}
				usedcnt[repin]=sofarcnt; //by3ml update l count elpage(Elrkm) elgdeda ele et7tt fl frame fl array bt3t el counters
            }
 
            dispPages();
        }
 
    }
    dispPgFaultCnt();
}

void secondchance()
{
    int usedbit[numFrames]; //array for frames numbers that detect it's used or not ( each element in this array have only 0 or 1 )
    int victimptr=0; //variable bst5dmo k pointer byfdl ylf zy elfifo bltrtyeb mn fo2 l t7t
    initialize();
    for(int i=0; i<numFrames; i++) //intialization for array of bits 
        usedbit[i]=0;
    for(int i=0; i<numOfPages; i++) 
    {
        if(isinFrames(seq[i])) //lw hyd5l rkm w hwa already mwgod fl frame by5li el usedbit bt3to b 1 bdl 0
        {
            cout<<"No page fault!\n"; 
            int pageIndex=getPgIndexInFrame(seq[i]); 
            if(usedbit[pageIndex]==0)  //if the usedbit corresponding to page was 0 make it 1 to show that it has been used for more than one time when it's in frame
                usedbit[pageIndex]=1;
        }
        else //lw hyd5l rkm (page) msh mwgod fl frames fhy3ml swapping
        {
            pgfaultcnt++;
            if(usedbit[victimptr]==1) //when swapping takes place if the frame has usedbit of 1 make it 0 and swap with the next victim
            {
                do
                {
                    usedbit[victimptr]=0;
                    victimptr++;
                    if(victimptr==numFrames) //lw wslt l a5r mkan fl frame 5li elvictim pointer yrg3 mn el2wl 5als mn fo2
                        victimptr=0;
                }
                while(usedbit[victimptr]!=0); //awl ma yla2i usedbit b2a f frame b2a b 0 y2f 3ndha l2n de htb2a elmkan ele hbdl feh dlw2ty
            }
            if(usedbit[victimptr]==0) //lw elcondition da et722 yb2a hna ht7sl 3mlit elswapping p page msh mwgoda fl frames 3nd el victimptr ele w2f 3leh
            {
                frames[victimptr]=seq[i];
                usedbit[victimptr]=1; //de trick msh fl algorithm bs de 34an n3lm a5r mkan est5dmanah w 3mlna feh swapping 34an y3dyeh w ynzl lle b3deh
                victimptr++;
            }
            dispPages();
 
        }
        if(victimptr==numFrames) //byrg3 mn 2wl 5als bl pointer 34an ylf mn awl wgded b3d ma bdl ma a5r victim fl frame el25yra
            victimptr=0;
    }
    dispPgFaultCnt();
}

int main()
{
	generateData();
	lfu();
	secondchance();
}

