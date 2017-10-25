#include <SM.h>
#include <State.h>
#include <OctoWS2811.h>


unsigned char bytecount;
char incomingByte[5]={
  0,0,0,0,0};


unsigned int jitter[4];
unsigned int flop[4];
unsigned int mover[4];
unsigned int r[4],g[4];
unsigned int b=10;

const int ledsPerStrip = 150;
const int m2off=150;
const int m3off=300;
const int m4off=450;
const int ccdelay=500;


DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

SM mach1(b1);
SM mach2(b2);
SM mach3(b3);
SM mach4(b4);

void setup(){

  leds.begin();

  for(int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i,0,0,0);
    leds.show();
  }
  Serial.begin(38400);
}

void loop(){

  while(Serial.available()&& bytecount < 6 ){

    if(Serial.available()){

      incomingByte[bytecount]=Serial.read();
      bytecount++;

    }




  }//end while

  bytecount=0;

  for(int i = 0;i<4;i++)
  {
    jitter[i]=int(random(3000,60000));
     
     Serial.print(r[i]);
     Serial.print("  ");
    
    
    //Serial.print(mover[i]);
  }
  Serial.println();
  

  EXEC(mach1);
  EXEC(mach2);
  EXEC(mach3);
  EXEC(mach4);

  leds.show();

delay(30);


}

State a1()
{
  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i,0,0,0);
  }
  //leds.show();
  int switcher=incomingByte[1]-48;

  switch(switcher){

  case 0:
    mach1.Set(b1);
    break;

  case 1:
    
    mach1.Set(d1);
    break;

  case 2: 
    mach1.Set(e1);
    break;
    
  case 3:
    mach1.Set(f1);
    break;
  
  case 4:
    mach1.Set(g1);
    break;
    
  case 5:
    mach1.Set(h1);
    break;
    
  case 6:
    mach1.Set(i1);
    break;
    
  case 7:
    mach1.Set(j1);
    break;
    
  case 8:
    mach1.Set(k1);
    break;
    
  default:
    mach1.Set(a1);
    break;

  }
}

State b1()
{ 
  bState(0);
  if(mach1.Timeout(500)) mach1.Set(c1);
}



State c1()
{
  
  cState(0);
  if(mach1.Statetime()>=jitter[0] && incomingByte[1]=='0') mach1.Set(b1);
  else if (incomingByte[1]!='0') mach1.Set(a1);
}



State d1()//for flag '1' red adjusted
{
  
  dfState(0,0);

  if(mach1.Statetime()%ccdelay<=10)
  {
    if(r[0]<=10) r[0]+=1;
  }

  if(incomingByte[1]!='1') mach1.Set(a1);
}//end state d1

State e1()
{
  
  egState(0,0);

  if(mach1.Statetime()%ccdelay<=10)
  {
    if(r[0]>0) r[0]-=1;
  }
  if(incomingByte[1]!='2') mach1.Set(a1);

}//end state e1

State f1()
{
  
 dfState(0,0);
 
  if(mach1.Statetime()%ccdelay<=10)
  {
    if(g[0]<=10) g[0]+=1;
  }

  if(incomingByte[1]!='3') mach1.Set(a1); 
  
  
}//end f1

State g1()
{
  egState(0,0);
  
  if(mach1.Statetime()%ccdelay<=10)
  {
    if(g[0]>0) g[0]-=1;
  }



  if(incomingByte[1]!='4') mach1.Set(a1);

  
}//end g1

State h1()
{
  hState(0,0);

  if(mach1.Statetime()%ccdelay<=10)
  {
    if(g[0]<=10) g[0]+=1;
    if(r[0]<=10) r[0]+=1;
  }

  if(incomingByte[1]!='5') mach1.Set(a1); 
  
  
}//end h1

State i1()
{
  
  iState(0,0);
  
  if(mach1.Statetime()%ccdelay<=10)
  {
    if(g[0]>0) g[0]-=1;
    if(r[0]>0) r[0]-=1;

  }



  if(incomingByte[1]!='6') mach1.Set(a1);

  
}//end i1

State j1()
{
  
  jkState(0,0);
   
  if(mach1.Statetime()%ccdelay<=10)
  {
    if(g[0]<=10) g[0]++;
    if(r[0]>0) r[0]--;
  }
  
  if(incomingByte[1]!='7') mach1.Set(a1); 
  
  
}//end h1

State k1()
{
  jkState(0,0);
  
  if(mach1.Statetime()%ccdelay<=10)
  {
    if(g[0]>0) g[0]--;
    if(r[0]<=10) r[0]++;

  }



  if(incomingByte[1]!='8') mach1.Set(a1);

  
}//end i1




///////////////////////////////////////////////////////////////////////////end machine one

State a2()
{
  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+m2off,0,0,0);
  }
  //leds.show();
  int switcher=incomingByte[2]-48;

  switch(switcher){

  case 0: 
    mach2.Set(b2);
    break;

  case 1: 
    mach2.Set(d2); 
    break;

  case 2: 
    mach2.Set(e2);
    break;
    
  case 3:
    mach2.Set(f2);
    break;
  
  case 4:
    mach2.Set(g2);
    break;
    
  case 5:
    mach2.Set(h2);
    break;
    
  case 6:
    mach2.Set(i2);
    break;
    
  case 7:
    mach2.Set(j2);
    break;
    
  case 8:
    mach2.Set(k2);
    break;
    
  default:
    mach2.Set(a2);
    break;


  }
}

State b2()
{
  
  bState(m2off);
  if(mach2.Timeout(500)) mach2.Set(c2);
  
}

State c2()
{
  cState(m2off);

  if(mach2.Statetime()>=jitter[1] && incomingByte[2]=='0') mach2.Set(b2);
  else if (incomingByte[2]!='0') mach2.Set(a2);
}

State d2()//for flag '1'
{
  dfState(m2off,1);

  if(mach2.Statetime()%ccdelay<=10)
  {
    if(r[1]<=10) r[1]+=1;
  }

  if(incomingByte[2]!='1') mach2.Set(a2);
}//end state d1

State e2()
{
  
  egState(m2off,1);

  if(mach2.Statetime()%ccdelay<=10)
  {
    if(r[1]>0) r[1]-=1;

  }


  if(incomingByte[2]!='2') mach2.Set(a2);


}//end state e2

State f2()
{
  dfState(m2off,1);
  
  if(mach2.Statetime()%ccdelay<=10)
  {
    if(g[1]<=10) g[1]+=1;
  }

  if(incomingByte[2]!='3') mach2.Set(a2); 
  
  
}//end f1

State g2()
{
  
  egState(m2off,1);
 
  if(mach2.Statetime()%ccdelay<=10)
  {
    if(g[1]>0) g[1]-=1;
  }



  if(incomingByte[2]!='4') mach2.Set(a2);

  
}//end g1

State h2()
{
  
  hState(m2off,1);
  
  if(mach2.Statetime()%ccdelay<=10)
  {
    if(g[1]<=10) g[1]+=1;
    if(r[1]<=10) r[1]+=1;
  }

  if(incomingByte[2]!='5') mach2.Set(a2); 
  
  
}//end h1

State i2()
{
  iState(m2off,1);
  
  if(mach2.Statetime()%ccdelay<=10)
  {
    if(g[1]>0) g[1]-=1;
    if(r[1]>0) r[1]-=1;
  }



  if(incomingByte[2]!='6') mach2.Set(a2);

  
}//end i1

State j2()
{
 
  jkState(m2off,1);
  
  
  if(mach2.Statetime()%ccdelay<=10)
  {
    if(g[1]<=10) g[1]++;
    if(r[1]>0) r[1]--;
  }

  if(incomingByte[2]!='7') mach2.Set(a2); 
  
  
}//end h1

State k2()
{
  jkState(m2off,1);
  
  if(mach2.Statetime()%ccdelay<=10)
  {
    if(g[1]>0) g[1]--;
    if(r[1]<=10) r[1]++;
  }

  if(incomingByte[2]!='8') mach2.Set(a2);

  
}//end i2




///////////////////////////////////////////////////////////////////////////////end machine two


State a3()
{
  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+m3off,0,0,0);
  }
  //leds.show();
  int switcher=incomingByte[3]-48;

  switch(switcher){

  case 0: 
    mach3.Set(b3);
    break;

  case 1: 
    mach3.Set(d3); 
    break;

  case 2: 
    mach3.Set(e3);
    break;
    
  case 3:
    mach3.Set(f3);
    break;
  
  case 4:
    mach3.Set(g3);
    break;
    
  case 5:
    mach3.Set(h3);
    break;
    
  case 6:
    mach3.Set(i3);
    break;
    
  case 7:
    mach3.Set(j3);
    break;
    
  case 8:
    mach3.Set(k3);
    break;
    
  default:
    mach3.Set(a3);
    break;


  }
}

State b3()
{
   
  bState(m3off);
  if(mach3.Timeout(500)) mach3.Set(c3);
}

State c3()
{
  cState(m3off);
 
  if(mach3.Statetime()>=jitter[2] && incomingByte[3]=='0') mach3.Set(b3);
  else if (incomingByte[3]!='0') mach3.Set(a3);
}

State d3()//for flag '1'
{
   dfState(m3off,2);
 
    if(mach3.Statetime()%ccdelay<=10)
    {
      if(r[2]<=10) r[2]+=1;
    }

  if(incomingByte[3]!='1') mach3.Set(a3);
}//end state d1

State e3()
{
 egState(m3off,2);
   

  if(mach3.Statetime()%ccdelay<=10)
  {
    if(r[2]>0) r[2]-=1;

  }


  if(incomingByte[3]!='2') mach3.Set(a3);


}//end state e2

State f3()
{
  dfState(m3off,2);
  
  if(mach3.Statetime()%ccdelay<=10)
  {
    if(g[2]<=10) g[2]+=1;
  }

  if(incomingByte[3]!='3') mach3.Set(a3); 
  
  
}//end f1

State g3()
{
  
  egState(m3off,2);
    
  if(mach3.Statetime()%ccdelay<=10)
  
  {
    if(g[2]>0) g[2]-=1;
  }



  if(incomingByte[3]!='4') mach3.Set(a3);

  
}//end g1

State h3()
{
  
  hState(m3off,2);
  
  if(mach3.Statetime()%ccdelay<=10)
  {
    if(g[2]<=10) g[2]+=1;
    if(r[2]<=10) r[2]+=1;
  }

  if(incomingByte[3]!='5') mach3.Set(a3); 
  
  
}//end h1

State i3()
{
  
  iState(m3off,2);
  
  if(mach3.Statetime()%ccdelay<=10)
  {
    if(g[2]>0) g[2]-=1;
    if(r[2]>0) r[2]-=1;
  }



  if(incomingByte[3]!='6') mach3.Set(a3);

  
}//end i1

State j3()
{
  
  jkState(m3off,2);
  
  if(mach3.Statetime()%ccdelay<=10)
  {
    if(g[2]<=10) g[2]++;
    if(r[2]>0) r[2]--;
  }

  if(incomingByte[3]!='7') mach3.Set(a3); 
  
  
}//end h1

State k3()
{
  jkState(m3off,0);
  
  if(mach3.Statetime()%ccdelay<=10)
  {
    if(g[2]>0) g[2]--;
    if(r[2]<=10) r[2]++;

  }



  if(incomingByte[3]!='8') mach3.Set(a3);

  
}//end i3

//////////////////////////////////////////////////////////////////////end machine 3

State a4()
{
  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+m4off,0,0,0);
  }
  //leds.show();
  int switcher=incomingByte[4]-48;

  switch(switcher){

  case 0: 
    mach4.Set(b4);
    break;

  case 1: 
    mach4.Set(d4); 
    break;

  case 2: 
    mach4.Set(e4);
    break;
    
  case 3:
    mach4.Set(f4);
    break;
  
  case 4:
    mach4.Set(g4);
    break;
    
  case 5:
    mach4.Set(h4);
    break;
    
  case 6:
    mach4.Set(i4);
    break;
    
  case 7:
    mach4.Set(j4);
    break;
    
  case 8:
    mach4.Set(k4);
    break;
    
  default:
    mach4.Set(a4);
    break;


  }
}

State b4()
{
  
  bState(m4off);
  if(mach4.Timeout(500)) mach4.Set(c4);
}

State c4()
{
  cState(m4off);
 
  if(mach4.Statetime()>=jitter[3] && incomingByte[4]=='0') mach4.Set(b4);
  else if (incomingByte[4]!='0') mach4.Set(a4);
}

State d4()//for flag '1'
{
   dfState(m4off,3);
 
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(r[3]<=10) r[3]+=1;
  }

  if(incomingByte[4]!='1') mach4.Set(a4);
}//end state d1

State e4()
{
  egState(m4off,3);
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(r[3]>0) r[3]-=1;
  }

  if(incomingByte[4]!='2') mach4.Set(a4);


}//end state e2

State f4()
{
  dfState(m4off,3);
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(g[3]<=10) g[3]+=1;
  }

  if(incomingByte[4]!='3') mach4.Set(a4); 
  
  
}//end f1

State g4()
{
  
 egState(m4off,3);
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(g[3]>0) g[3]-=1;

  }

  if(incomingByte[4]!='4') mach4.Set(a4);

  
}//end g1

State h4()
{
  
  hState(m4off,3);
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(g[3]<=10) g[3]+=1;
    if(r[3]<=10) r[3]+=1;
  }

  if(incomingByte[4]!='5') mach4.Set(a4); 
  
  
}//end h1

State i4()
{
  
  iState(m4off,3);
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(g[3]>0) g[3]-=1;
    if(r[3]>0) r[3]-=1;
  }

  if(incomingByte[4]!='6') mach4.Set(a4);

  
}//end i1

State j4()
{
 
  jkState(m4off,3);
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(g[3]<=10) g[3]++;
    if(r[3]>0) r[3]--;
  }

  if(incomingByte[4]!='7') mach4.Set(a4); 
  
  
}//end h1

State k4()
{
  jkState(m4off,3);
  
  
  if(mach4.Statetime()%ccdelay<=10)
  {
    if(g[3]>0) g[3]--;
    if(r[3]<=10) r[3]++;

  }



  if(incomingByte[4]!='8') mach4.Set(a4);

  
}//end i4

void particle (int mover_,int offset,int dir,int r, int g, int b)
{
  
  
      leds.setPixel(mover_+offset,r,g,b);
      leds.setPixel(mover_+offset+(1*dir),r,g,b);
      leds.setPixel(mover_+offset+(2*dir),r,g,b);
      leds.setPixel(mover_+offset+(3*dir),r,g,b);
      leds.setPixel(mover_+offset+(4*dir),r,g,b);
      leds.setPixel(mover_+offset+50,r,g,b);
      leds.setPixel(mover_+offset+50+(1*dir),r,g,b);
      leds.setPixel(mover_+offset+50+(2*dir),r,g,b);
      leds.setPixel(mover_+offset+50+(3*dir),r,g,b);
      leds.setPixel(mover_+offset+50+(4*dir),r,g,b);
      leds.setPixel(mover_+offset+100,r,g,b);
      leds.setPixel(mover_+offset+100+(1*dir),r,g,b);
      leds.setPixel(mover_+offset+100+(2*dir),r,g,b);
      leds.setPixel(mover_+offset+100+(3*dir),r,g,b);
      leds.setPixel(mover_+offset+100+(4*dir),r,g,b);
}

void bState (int offset)
{
     int beg,len; 
  
  if(!mach2.Timeout(50)){
     beg = int(random(150));
     len = int(random(150));
  
  for (int i = 0;i<ledsPerStrip;i++)
    {
      if(i<beg) leds.setPixel(i+offset,0,0,0);
      else if(i>=beg && i<beg+len) leds.setPixel(i+offset,255,255,255);
      else if (i>beg+len) leds.setPixel(i+offset,0,0,0);
    }
  }
}//end bstate

void cState (int offset)
{
 
 for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+offset,0,0,0);
  }
  
}//end cState

void dfState(int offset,int mn)
{
 
 int dir=1;

  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+offset,r[mn],g[mn],b);
  }
    
  //particle(mover[0],0,dir);
  particle(mover[mn],offset,1,255,255,255);
  particle(mover[mn]*2,offset,1,255,255,255);
  particle(50-mover[mn],offset,1,0,0,0);
  particle(mover[mn]+30,offset,1,255,255,255);
  particle(70-mover[mn],offset,1,0,0,0);

  

  if(mover[mn]<=50)
  {
    mover[mn]+=dir;
  }

  else mover[mn]=0; 
}//end dfState

void egState(int offset,int mn)
{
 
 int dir = -1;
  if(mover[mn]> 0)
  {
    mover[mn]+=dir;
  }

  else mover[mn]=50;


  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+offset,r[mn],g[mn],b);
  } 
    particle(mover[mn],offset,dir,0,0,0);
    particle(mover[mn]*2,offset,dir,255,255,255);
    particle(mover[mn]*2+5,offset,dir,255,255,255);
    particle(50-mover[mn],offset,dir,10,10,10);
    particle(70-mover[mn]+int(random(-10,5)),offset,dir,20,20,20);
    
}

void hState(int offset, int mn)
{
 
  int dir = 1;
  int spark[4];
 
  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+offset,r[mn],g[mn],b);
  } 
  
  for (int i = 0;i<4;i++)
  {
    spark[i]=int(random(70));
  }
  
  spark[1]-=90;
  spark[3]-=90;
  particle(mover[mn]+int(random(10)),offset,dir,spark[1],spark[1],spark[1]);
  particle(mover[mn],offset,dir,spark[1],spark[1],spark[1]);
  particle(mover[mn]+5,offset,dir,spark[0],spark[0],spark[0]);
  particle(mover[mn]+50+int(random(10)),offset,dir,spark[3],spark[3],spark[3]);
  particle(mover[mn]+50,offset,dir,spark[3],spark[3],spark[3]);
  particle(mover[mn]+55,offset,dir,spark[2],spark[2],spark[2]);
  
  if(mover[mn]<=50)
  {
    mover[mn]+=dir;
  }

  else mover[mn]=0; 
}// end hState

void iState(int offset, int mn)
{
 
 int dir = -1;
 int spark[4];
  
  if(mover[mn]> 5)
  {
    mover[mn]+=dir;
  }

  else mover[mn]=50;


  for (int i = 0;i<ledsPerStrip;i++)
  {
    leds.setPixel(i+offset,r[mn],g[mn],b);
  } 
  
  for (int i = 0;i<4;i++)
  {
    spark[i]=int(random(170));
  }
  
  particle(mover[mn]+int(random(5)),offset,dir,spark[1],spark[1],spark[1]);
  particle(mover[mn],offset,dir,spark[1],spark[1],spark[1]);
  particle(mover[mn]+5,offset,dir,spark[0],spark[0],spark[0]);
  particle(mover[mn]+50+int(random(5)),offset,dir,spark[3],spark[3],spark[3]);
  particle(mover[mn]+50,offset,dir,spark[3],spark[3],spark[3]);
  particle(mover[mn]+55,offset,dir,spark[2],spark[2],spark[2]);
}//end iState

void jkState(int offset, int mn)
{
  
  int dir = 1;
 
  for (int i = 0;i<ledsPerStrip;i++)
    {
      leds.setPixel(i+offset,0,0,0);
    } 
  
  
    particle(mover[mn],offset,dir,255,255,255);
    particle(mover[mn]+5,offset,dir,50,50,50);
    particle(mover[mn]-5,offset,dir,50,50,50);
    particle(mover[mn]+int(random(-20,20)),offset,dir,r[mn],g[mn],0);
    particle(mover[mn]+int(random(-5,5)),offset,dir,r[mn],g[mn],0);
    particle(mover[mn]+int(random(-10,10)),offset,dir,r[mn],g[mn],0);
  
  mover[mn]+=int(random(-2,3));
  
  if(mover[mn] < 0) mover[mn] = 0;
  if(mover[mn] > 50) mover[mn] = 50;
  
}


