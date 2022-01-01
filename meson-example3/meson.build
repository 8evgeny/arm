project('startingmeson', 'cpp',
 version : '0.1',
 default_options : ['warning_level=3', 'cpp_std=c++14'])
boost_dep = dependency('boost', modules : ['filesystem']) 
executable('startingmeson',
 'main.cpp',
 dependencies : boost_dep,
 install : true)
