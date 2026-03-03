project('PolSARproSim', 'c',
  version : '1.0.0',
  default_options : ['warning_level=2', 'c_std=c11']
)

# Dependencies
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)
thread_dep = dependency('threads')
xml_dep = dependency('libxml-2.0')

# Include Directories
inc = include_directories('../include')

# Common Compiler Flags
add_project_arguments('-DENABLE_THREADS', language : 'c')

# Source Lists
pspsim_src = [
  'src/PolSARproSim.c', 'src/Allometrics.c', 'src/Attenuation.c', 'src/Branch.c', 'src/c3Vector.c',
  'src/c33Matrix.c', 'src/Complex.c', 'src/Cone.c', 'src/Crown.c', 'src/Cylinder.c', 'src/d3Vector.c',
  'src/d33Matrix.c', 'src/Drawing.c', 'src/Facet.c', 'src/GraphicIMage.c', 'src/GrgCyl.c', 'src/Ground.c',
  'src/InfCyl.c', 'src/JLkp.c', 'src/Jnz.c', 'src/Leaf.c', 'src/LightingMaterials.c', 'src/MonteCarlo.c',
  'src/Perspective.c', 'src/Plane.c', 'src/PolSARproSim_Direct_Ground.c', 'src/PolSARproSim_Forest.c',
  'src/PolSARproSim_Procedures.c', 'src/PolSARproSim_Progress.c', 'src/PolSARproSim_Short_Vegi.c',
  'src/Ray.c', 'src/RayCrownIntersection.c', 'src/Realisation.c', 'src/SarIMage.c', 'src/Shuffling.c',
  'src/Sinc.c', 'src/soilsurface.c', 'src/Spheroid.c', 'src/Tree.c', 'src/YLkp.c', 'src/read_parfile.c',
  'src/read_forest.c', 'src/read_allometry.c'
]

# Executable definitions
executable('pspsim',
  pspsim_src,
  include_directories : inc,
  dependencies : [m_dep, thread_dep, xml_dep],
  install : true
)

# Optional: Uncomment if you want to build the others
# executable('pspsimfekz_dev', ['PolSARproSim_FE_Kz.c', 'matrix.c', 'util.c'], 
#            include_directories : inc, dependencies : [thread_dep], install : true)

# executable('pspsim_imgsize_dev', ['PolSARproSim_ImgSize.c'], 
#            include_directories : inc, dependencies : [thread_dep], install : true)

