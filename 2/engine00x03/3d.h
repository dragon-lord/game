#ifndef D3_H
#define D3_H
#include <stdio.h>
#include <math.h>
#include "../math.h"
#include "player.h"
#include "render.h"
//									0					1					2					3				4					5				6				7
float POINTS[14][3]={{-1,-1,-1},{-1,-1,1},{1,-1,1},{1,-1,-1},{-1,1,-1},{-1,1,1},{1,1,1},{1,1,-1},{0,0,-1},{1,0,0},{0,0,1},{-1,0,0},{0,-1,0},{0,1,0}};
//									0						1							2							3						4					5
//			6					7						8						9							10				11				12					13
//			14				15
float POINTS4[16][4]={{-1,-1,-1,-1},{1,-1,-1,-1},{-1,1,-1,-1},{1,1,-1,-1},{-1,-1,1,-1},{1,-1,1,-1},{-1,1,1,-1},{1,1,1,-1},{-1,-1,-1,1},{1,-1,-1,1},{-1,1,-1,1},{1,1,-1,1},{-1,-1,1,1},{1,-1,1,1},{-1,1,1,1},{1,1,1,1}};
float CUBE[24][3]={{0,3,8},{3,7,8},{7,4,8},{4,0,8},{2,3,9},{3,7,9},{7,6,9},{6,2,9},{1,2,10},{2,6,10},{6,5,10},{5,1,10},{0,1,11},{1,5,11},{5,4,11},{4,0,11},{0,1,12},{1,2,12},{2,3,12},{3,0,12},{4,5,13},{5,6,13},{6,7,13},{7,4,13}};
float CUBET[6][5]={{8,0,3,7,4},{9,2,3,7,6},{10,1,2,6,5},{11,0,1,5,4},{12,0,1,2,3},{13,4,5,6,7}};
CUBEO[6][4]={{0,1,2,3},{0,3,7,4},{0,4,5,1},{1,2,6,5},{2,3,7,6},{4,5,6,7}};
float EDGES[12][2]={{0,1},{0,3},{0,4},{1,2},{1,5},{2,3},{2,6},{3,7},{4,5},{4,7},{5,6},{6,7}};
float EDGES4[32][2]={{0,1},{0,2},{0,4},{0,8},{1,3},{1,5},{1,9},{2,3},{2,6},{2,10},{3,7},{3,11},{4,5},{4,6},{4,12},{5,7},{5,13},{6,7},{6,14},{7,15},{8,9},{8,10},{8,12},{9,11},{9,13},{10,11},{10,14},{11,15},{12,13},{12,14},{13,15},{14,15}};

float* D3(struct Cam3 cam,struct Vec3 pnt);
/*float* Cube(struct Cam cam,float pnt[3]);/*/
//float* intemediary(struct Cam cam, struct Vec3 pnt);
struct Vec3 intemediary(struct Cam3 cam,float pnt[3]);
void Draw_cube(struct Cam3 cam,float pnt[3],Uint32 color);
void Draw_hyperCube(struct Cam4 cam,float pnt[4],Uint32 color);
void Draw_crossCube(struct Cam3 cam,float pnt[3],Uint32 color);
void Draw_texturedCube(struct Cam3 cam,float pnt[3],int tex[2],FILE *map,int size[3]);
//*/

int draw=1;

//IMPLIMENT0347

float* D3(struct Cam3 cam,struct Vec3 pnt){
	cam.fwd=Vec3_norm(cam.fwd);
	pnt=Vec3_norm(pnt);
	float theta=Vec3_angle(cam.fwd,pnt);
	float D2[2];
	float fov=5;
	if(theta>0.770015)
		draw=0;
	if(theta>M_PI/2-.1 && theta<M_PI/2+.1)
		theta=M_PI/2-.1;
	if(theta>M_PI/2){
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=-100*Vec3_length(pnt)*cos(theta)+(swidth/2);
		D2[1]=-100*Vec3_length(pnt)*sin(theta)+(-sheight/2);
	}else{
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=100*Vec3_length(pnt)*cos(theta)+(swidth/2);
		D2[1]=100*Vec3_length(pnt)*sin(theta)+(-sheight/2);
	}
	/*if(cam.shift==1){
		D2[1]+=100;
	}//*/
	return D2;
}

/*float* intemediary(struct Cam cam, struct Vec3 pnt){
	//pnt=Vec3_rot(pnt,cam.up,Vec3_angle(pnt,cam.fwd)*2/3);
	return D3(cam,pnt);
}//*/

struct Vec3 intemediary(struct Cam3 cam,float pnt0[3]){
	float coord[3]={cam.x,cam.y,cam.z};
	struct Vec3 pnt=Vec3_newv(pnt0,coord);

	if(pnt0[0]>5 && pnt0[0]<12 && pnt0[2]>10 && pnt0[2]<14){
		//pnt=Vec3_rot(pnt,Vec3_cross(cam.fwd,pnt),Vec3_angle(pnt,cam.fwd)*2/3);
		pnt0[0]=(pnt0[0]-5)/2+5;
	}

	pnt=Vec3_newv(pnt0,coord);
	printf("(%f,%f,%f)\n",cam.x,cam.y,cam.z);
	return pnt;
}

/*void Draw_cube(struct Cam cam,float pnt[3],Uint32 color){
	float coord[3]={cam.x,cam.y,cam.z};
	int arr[3]={1,1,1};
	for(int i=0;i<24;i++){
		for(int j=0;j<3;j++){
			draw=1;
			int k=CUBE[i][j];
			float* D2=D3(cam,Vec3_newv(POINTS[k],coord));
			x[i]=D2[0];
			y[i]=D2[1];
			if(draw==0){
				arr[i]=0;
			}else{
				arr[i]=1;
			}
		}
		if(arr[0]==1||arr[1]==1||arr[2]==1)
			Draw_triangle(x,y,color);
	}
}/* /
void Draw_cube(struct Cam cam,float pnt[3],Uint32 color){
	float arr[14][2];
	int d[14];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<14;i++){
		draw=1;
		float* D2=D3(cam,Vec3_newv(POINTS[i],coord));
		arr[i][0]=D2[0];
		arr[i][1]=D2[1];
		if(draw==1){
			d[i]=1;
		}else{
			d[i]=0;
		}
	}
	int temp=0;
	for(int i=0;i<14;i++){
		//printf("%i",d[i]);
		if(d[i]==1)
			temp=1;
	}
	//printf("\n");
	if(temp==1){
		for(int i=0;i<24;i++){
			int index[3]={CUBE[i][0],CUBE[i][1],CUBE[i][2]};
			int num[6]={arr[index[0]][0],arr[index[1]][0],arr[index[2]][0],arr[index[0]][1],arr[index[1]][1],arr[index[2]][1]};
			short x[3]={(short)(num[0]),(short)(num[1]),(short)(num[2])};
			short y[3]={(short)(-num[3]),(short)(-num[4]),(short)(-num[5])};
			Draw_triangle(x,y,color);
		}
	}
}/*/
void Draw_cube(struct Cam3 cam,float pnt[3],Uint32 color){
	float arr[14][2];
	int d[14];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<14;i++){
		draw=1;
		float pnt1[3]={POINTS[i][0]+pnt[0]*2,POINTS[i][1]+pnt[1]*2,POINTS[i][2]+pnt[2]*2};
		float* D2=D3(cam,Vec3_newv(pnt1,coord));
		arr[i][0]=D2[0];
		arr[i][1]=D2[1];
		if(draw==1){
			d[i]=1;
		}else{
			d[i]=0;
		}
	}
	int temp=0;
	for(int i=0;i<14;i++){
		//printf("%i",d[i]);
		if(d[i]==1)
			temp=1;
	}

	if(temp==1){
		for(int i=0;i<6;i++){
			int index[4]={CUBEO[i][0],CUBEO[i][1],CUBEO[i][2],CUBEO[i][3]};
			int num[8]={arr[index[0]][0],arr[index[1]][0],arr[index[2]][0],arr[index[3]][0],arr[index[0]][1],arr[index[1]][1],arr[index[2]][1],arr[index[3]][1]};
			short x[4]={(short)(num[0]),(short)(num[1]),(short)(num[2]),(short)(num[3])};
			short y[4]={(short)(-num[4]),(short)(-num[5]),(short)(-num[6]),(short)(-num[7])};
			Draw_rect(x,y,color);
		}
	}

}//*/

void Draw_hyperCube(struct Cam4 cam,float pnt[4],Uint32 color){
	struct Vec4 zed=Vec4_newn(cam.w+pnt[0],cam.x+pnt[1],cam.y+pnt[2],cam.z+pnt[3]);
	struct Vec4 up=Vec4_ortho(cam.fwd,cam.ana,cam.rght);

	float d=cam.fwd.w*zed.w+cam.fwd.x*zed.x+cam.fwd.y*zed.y+cam.fwd.z*zed.z;
	int e[32];
	for(int i=0;i<32;i++){
		e[i]=0;
	}
	int p[16];
	int pnts=0;
	int pos=0;
	int neg=0;
	int on=0;

	for(int i=0;i<16;i++){
		float r=cam.fwd.w*POINTS4[i][0]+cam.fwd.x*POINTS4[i][1]+cam.fwd.y*POINTS4[i][2]+cam.fwd.z*POINTS4[i][3];
		if(r==d){
			on++;
			p[i]=0;
		}else if(r>d){
			pos++;
			p[i]=1;
		}else{
			neg++;
			p[i]=-1;
		}
		//printf("%i\n",p[i]);
	}
	//printf(" %i,%i,%i\n",on,pos,neg);

	for(int i=0;i<32;i++){
		int temp[2]={EDGES[i][0],EDGES[i][1]};
		if((p[temp[0]]==-1 && p[temp[1]]==1) || (p[temp[0]]==1 && p[temp[1]]==-1)){
			e[pnts]=i;
			pnts++;
		}
	}/*
	for(int i=0;i<pnts;i++){
		printf("%i\n",e[i]);
	}
	printf(" %i\n",pnts);//*/
	int f[on];
	int g=0;
	for(int i=0;i<8;i++){
		if(p[i]==0){
			f[g]=i;
			g++;
		}
	}
	struct Vec3 points[pnts+on];
	struct Vec4 vec=Vec4_ortho(cam.ana,cam.up,cam.rght);
	for(int i=0;i<pnts;i++){
		int temp0=EDGES4[e[i]][0];
		int temp1=EDGES4[e[i]][1];
		struct Vec4 p0=Vec4_newn(POINTS4[temp0][0],POINTS4[temp0][1],POINTS4[temp0][2],POINTS4[temp0][3]);
		struct Vec4 p1=Vec4_newn(POINTS4[temp1][0],POINTS4[temp1][1],POINTS4[temp1][2],POINTS4[temp1][3]);
		//struct Vec3 pp=Vec3_addv(Vec3_subv(intersection(cam.fwd,Vec3_newn(cam.x,cam.y,cam.z),Vec3_subv(p0,p1),p0),Vec3_newn(cam.x,cam.y,cam.z)),Vec3_newn(pnt[0],pnt[1],pnt[2]));
		struct Vec4 pp=intersection4(cam.fwd,zed,Vec4_subv(p0,p1),p0);
		points[i]=Vec3_newn((Vec4_dot(pp,cam.rght)-Vec4_dot(zed,cam.rght)),(Vec4_dot(pp,up)-Vec4_dot(zed,up)),(Vec4_dot(pp,vec)-Vec4_dot(zed,vec)));
		//printf("(%f,%f)\n",Vec3_dot(pp,cam.rght),Vec3_dot(pp,up));
		//printf("p0:(%f,%f,%f)\n p1:(%f,%f,%f)\n",p0.x,p0.y,p0.z,p1.x,p1.y,p1.z);
		//x[i]=(short)(points[i].x);
		//y[i]=(short)(points[i].y);
		//printf("%i:(%i,%i)\n",i,x[i],y[i]);
	}
	for(int i=0;i<on;i++){
		struct Vec4 pp=Vec4_newn(POINTS4[f[i]][0],POINTS4[f[i]][1],POINTS4[f[i]][2],POINTS4[f[i]][3]);
		points[i+pnts]=Vec3_newn(Vec4_dot(pp,cam.rght),Vec4_dot(pp,up),Vec4_dot(pp,vec));
	}
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<pnts+on;i++){
		//float pnt1[3]={points[i].x,points[i].y,points[i].z};
		float pnt1[3]={0,0,1};
		float* D2=D3(Cam3_frm4(cam),Vec3_newv(pnt1,coord));
		short x[4]={D2[0],D2[0]+.1,D2[0]+.1,D2[0]};
		short y[4]={D2[1]+.1,D2[1]+.1,D2[1],D2[1]};
		Draw_rect(x,y,color);
		//printf("%i:(%f,%f,%f),(%f,%f)\n",i,points[i].x,points[i].y,points[i].z,D2[0],D2[1]);
	}
}

void Draw_crossCube(struct Cam3 cam,float pnt[3],Uint32 color){
	/*struct Vec3 vec=Vec3_subv(Vec3_newn(cam.x,cam.y,cam.z),Vec3_newn(pnt[0],pnt[1],pnt[2]));
	if((Vec3_equal(cam.fwd,Vec3_norm(Vec3_cross(cam.rght,vec)))==1 || Vec3_equal(cam.fwd,Vec3_norm(Vec3_cross(cam.rght,vec)))==1)!=1){
		printf("1\n");
		//end;
	}//*/
	struct Vec3 zed=Vec3_newn(cam.x+pnt[0],cam.y+pnt[1],cam.z+pnt[2]);
	struct Vec3 up=Vec3_cross(cam.fwd,cam.rght);
	//printf("(%f,%f,%f)\n",cam.rght.x,cam.rght.y,cam.rght.z);
	float d=cam.fwd.x*zed.x+cam.fwd.y*zed.y+cam.fwd.z*zed.z;
	int e[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	int p[8];
	int pnts=0;
	int pos=0;
	int neg=0;
	int on=0;
	for(int i=0;i<8;i++){
		float r=cam.fwd.x*POINTS[i][0]+cam.fwd.y*POINTS[i][1]+cam.fwd.z*POINTS[i][2];
		if(r==d){
			on++;
			p[i]=0;
		}else if(r>d){
			pos++;
			p[i]=1;
		}else{
			neg++;
			p[i]=-1;
		}
		//printf("%i\n",p[i]);
	}
	//printf(" %i,%i,%i\n",on,pos,neg);
	for(int i=0;i<12;i++){
		int temp[2]={EDGES[i][0],EDGES[i][1]};
		if((p[temp[0]]==-1 && p[temp[1]]==1) || (p[temp[0]]==1 && p[temp[1]]==-1)){
			e[pnts]=i;
			pnts++;
		}
	}/*/
	for(int i=0;i<12;i++){
		int temp[2]={edges[i][0],edges[i][1]};
		if((p[temp[0]]==-1 && p[temp[1]]==1) || (p[temp[0]]==1 && p[temp[1]]==-1)){
			e[pnts]=i;
			pnts++;
		}
	}//*/
	int f[on];
	int g=0;
	for(int i=0;i<8;i++){
		if(p[i]==0){
			f[g]=i;
			g++;
		}
	}
	//struct Vec3 up=Vec3_ortho
	short x[pnts+on];
	short y[pnts+on];
	struct Vec2 points[pnts+on];
	for(int i=0;i<pnts;i++){
		int temp0=EDGES[e[i]][0];
		int temp1=EDGES[e[i]][1];
		struct Vec3 p0=Vec3_newn(POINTS[temp0][0],POINTS[temp0][1],POINTS[temp0][2]);
		struct Vec3 p1=Vec3_newn(POINTS[temp1][0],POINTS[temp1][1],POINTS[temp1][2]);
		//struct Vec3 pp=Vec3_addv(Vec3_subv(intersection(cam.fwd,Vec3_newn(cam.x,cam.y,cam.z),Vec3_subv(p0,p1),p0),Vec3_newn(cam.x,cam.y,cam.z)),Vec3_newn(pnt[0],pnt[1],pnt[2]));
		struct Vec3 pp=intersection3(cam.fwd,zed,Vec3_subv(p0,p1),p0);
		points[i]=Vec2_newn((width/2)+((Vec3_dot(pp,cam.rght)-Vec3_dot(zed,cam.rght))*100),(height/2)-((Vec3_dot(pp,up)-Vec3_dot(zed,up))*100));
		//printf("(%f,%f)\n",Vec3_dot(pp,cam.rght),Vec3_dot(pp,up));
		//printf("p0:(%f,%f,%f)\n p1:(%f,%f,%f)\n",p0.x,p0.y,p0.z,p1.x,p1.y,p1.z);
		//x[i]=(short)(points[i].x);
		//y[i]=(short)(points[i].y);
		//printf("%i:(%i,%i)\n",i,x[i],y[i]);
	}/*/
	struct Vec2 points[pnts+on];
	short x[pnts+on];
	short y[pnts+on];
	for(int i=0;i<pnts;i++){
		int temp=EDGES[e[i]][0];
		struct Vec3 p0=Vec3_newn(POINTS[temp][0]+pnt[0]-cam.x,POINTS[temp][1]+pnt[1]-cam.y,POINTS[temp][2]+pnt[2]-cam.z);
		temp=EDGES[e[i]][1];
		struct Vec3 vec=Vec3_subv(Vec3_newn(POINTS[temp][0]+pnt[0]-cam.x,POINTS[temp][1]+pnt[1]-cam.y,POINTS[temp][2]+pnt[2]-cam.z),p0);
		struct Vec3 pp=intersection(cam.fwd,Vec3_newn(cam.x,cam.y,cam.z),vec,p0);
		points[i]=Vec2_newn((width/2)+100*Vec3_dot(pp,cam.rght),(height/2)-(100*Vec3_dot(pp,cam.up)));
		printf("%i:(%i,%i)\n",i,x[i],y[i]);
	}/*/
	for(int i=0;i<on;i++){

		struct Vec3 pp=Vec3_newn(POINTS[f[i]][0],POINTS[f[i]][1],POINTS[f[i]][2]);
		points[i+pnts]=Vec2_newn((width/2)+(Vec3_dot(pp,cam.rght)*100),(height/2)-(Vec3_dot(pp,up)*100));
	}//*/
	points=convexHull(points,pnts+on);
	for(int i=0;i<pnts+on;i++){
		x[i]=(short)points[i].x;
		y[i]=(short)points[i].y;
	}
	Draw_poly(x,y,pnts,color);
}

void Draw_texturedCube(struct Cam3 cam,float pnt[3],int tex[2],FILE *map,int size[3]){
	float arr[14][2];
	int d[14];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<14;i++){
		draw=1;
		float pnt1[3]={POINTS[i][0]+pnt[0]*2,POINTS[i][1]+pnt[1]*2,POINTS[i][2]+pnt[2]*2};
		float* D2=D3(cam,/*intemediary(cam,pnt1));/*/Vec3_newv(pnt1,coord));//*/
		arr[i][0]=D2[0];
		arr[i][1]=D2[1];
		if(draw==1){
			d[i]=1;
		}else{
			d[i]=0;
		}
	}
	int temp=0;
	for(int i=0;i<14;i++){
		//printf("%i",d[i]);
		if(d[i]==1)
			temp=1;
	}
	//printf("\n");
	if(temp==1){
		/*for(int i=0;i<24;i++){
			int index[3]={CUBE[i][0],CUBE[i][1],CUBE[i][2]};
			int num[6]={arr[index[0]][0],arr[index[1]][0],arr[index[2]][0],arr[index[0]][1],arr[index[1]][1],arr[index[2]][1]};
			short x[3]={(short)(num[0]),(short)(num[1]),(short)(num[2])};
			short y[3]={(short)(num[3]),(short)(num[4]),(short)(num[5])};
			Draw_triangle(x,y,color);
		}//*/
		int e[3]={3,4,0};
		int num=0;
		if(cam.x>pnt[0]*2+1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]+1)*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[0]!=size[0]-1){
				e[0]=6;
			}else{
				e[0]=1;
			}
		}else if(cam.x<pnt[0]*2-1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]-1)*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[0]!=0){
				e[0]=6;
			}else{
				e[0]=3;
			}
		}else{e[0]=6;}
		if(cam.y>pnt[1]*2+1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]+size[0])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[1]!=size[1]-1){
				e[1]=6;
			}else{
				e[1]=5;
			}
		}else if(cam.y<pnt[1]*2-1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]-size[0])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[1]!=0){
				e[1]=6;
			}else{
				e[1]=4;
			}
		}else{e[1]=6;}
		if(cam.z>pnt[2]*2+1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]+size[0]*size[1])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			//if(num==5&&pnt[2]==4)
			//	printf("hi\n");
			if(num!=0 && pnt[2]!=size[2]-1){
				e[2]=6;
			}else{
				e[2]=2;
			}
		}else if(cam.z<pnt[2]*2-1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]-size[0]*size[1])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[2]!=0){
				e[2]=6;
			}else{
				e[2]=0;
			}
		}else{e[2]=6;}
		/*if(tex[0]==1 && tex[1]==1){
			printf("p:(%f,%f,%f)\n",pnt[0],pnt[1],pnt[2]);
			printf("e:(%i,%i,%i)\n",e[0],e[1],e[2]);
		}//*/
		fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0])*sizeof(int),SEEK_SET);
		fread(&num,sizeof(int),1,map);
		//if(num==5)
		//	printf("%i:(%i,%i,%i),(%f,%f,%f)\n",num,e[0],e[1],e[2],pnt[0],pnt[1],pnt[2]);
		for(int i=0;i<3;i++){
			if(e[i]!=6){
				int index[5]={CUBET[e[i]][0],CUBET[e[i]][1],CUBET[e[i]][2],CUBET[e[i]][3],CUBET[e[i]][4]};
				float verticies[10]={
					arr[index[0]][0],arr[index[0]][1],
					arr[index[1]][0],arr[index[1]][1],
					arr[index[2]][0],arr[index[2]][1],
					arr[index[3]][0],arr[index[3]][1],
					arr[index[4]][0],arr[index[4]][1],
				};
				Draw_face(verticies,tex);//*/
			}
		}
	}
}

#endif //D3_H