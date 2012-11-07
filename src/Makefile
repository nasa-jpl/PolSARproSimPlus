HOME = /Users/rahmed/PolSARproSIM
SRCDIR = $(HOME)/src
LIBDIR = $(HOME)/lib
INCDIR = -I$(HOME)/include
BINDIR = $(HOME)/bin

CC = gcc
CFLAGS = -g -Wall -DENABLE_THREADS $(INCDIR) 
LDFLAGS = -lm -lxml2
RM = rm -rf

#PROGS = pspsim_dev pspsimfekz_dev pspsim_imgsize_dev
PROGS = pspsim_dev

PSPSIMOBJS = PolSARproSim.o Allometrics.o Attenuation.o Branch.o c3Vector.o c33Matrix.o Complex.o Cone.o Crown.o Cylinder.o d3Vector.o d33Matrix.o Drawing.o Facet.o GraphicIMage.o GrgCyl.o Ground.o InfCyl.o JLkp.o Jnz.o Leaf.o LightingMaterials.o MonteCarlo.o Perspective.o Plane.o PolSARproSim_Direct_Ground.o PolSARproSim_Forest.o PolSARproSim_Procedures.o PolSARproSim_Progress.o PolSARproSim_Short_Vegi.o Ray.o RayCrownIntersection.o Realisation.o SarIMage.o Shuffling.o Sinc.o soilsurface.o Spheroid.o Tree.o YLkp.o

PSPFEKZOBJS= PolSARproSim_FE_Kz.o matrix.o util.o

PSPIMGSZOBJS=PolSARproSim_ImgSize.o

all: $(PROGS)

pspsim_dev: $(PSPSIMOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(PSPSIMOBJS) -o pspsim_dev

pspsimfekz_dev: $(PSPFEKZOBJS)
	$(CC) $(CFLAGS) $(PSPFEKZOBJS) -o pspsimfekz_dev

pspsim_imgsize_dev: $(PSPIMGSZOBJS) 
	$(CC) $(CFLAGS) $(PSPIMGSZOBJS) -o pspsim_imgsize_dev

install: $(PROGS)
	mv -f $(PROGS) $(BINDIR)

clean: 
	rm -f $(PSPSIMOBJS) $(PSPIMGSZOBJS) $(PSPFEKZOBJS) $(PROGS)
