from waflib.Tools.compiler_cxx import cxx_compiler
#from scripts.waf import utils
#!/usr/bin/env python3
import os
import sys
import subprocess

APPNAME = 'querycpp'
VERSION = '0.0.1' #TODO: REPLACE 

cxx_compiler['linux'] = ['clang++']

def options(opt) :
    opt.load('compiler_cxx')

def configure(cnf) :
    cnf.load('compiler_cxx')

    link_flags = ['-pthread']
    cxx_flags = ['-std=c++17', '-Wall', '-Wextra', '-O3']
    
    if sys.platform == 'darwin':
        link_flags.append('-L/usr/local/opt/llvm/lib')
        cxx_flags.append('-stdlib=libc++')

    cnf.env.append_value('CXXFLAGS', cxx_flags)        
    cnf.env.append_value('LINKFLAGS',
                         link_flags)
    
def build(bld):

    bld(name = '{!s}-includes'.format(APPNAME),
        includes='./include/querycpp',
        export_includes='./include/querycpp')
    
    bld.stlib(name = APPNAME,
        features = 'cxx cxxstlib',
        target='{!s}'.format(APPNAME),
        includes='../src',
        lib = ['fmt'],
        source=bld.path.ant_glob('src/{!s}/**/*.cpp'.format(APPNAME)),
        use=['{!s}-includes'.format(APPNAME)]
    )

    bld(name = '{!s}-test-includes'.format(APPNAME),
        includes='./include',
        export_includes='./include')
    

#    bld.recurse('test/test_database_data_types')
    bld.recurse('test/test_column')
    bld.recurse('test/test_table')
    bld.recurse('test/test_query')
    
def test(ctx):
#    subprocess.call(['./build/test/test_database_data_types/test_database_data_types'], encoding='utf-8')        
    subprocess.call(['./build/test/test_column/test_column'], encoding='utf-8')
    subprocess.call(['./build/test/test_table/test_table'], encoding='utf-8')
    subprocess.call(['./build/test/test_query/test_query'], encoding='utf-8')                

