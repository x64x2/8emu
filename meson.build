project(
        '8emu',
        ['cpp'],
        default_options: ['c_std=c23', 'cpp_std=c++23'],
)

add_global_arguments(
  '-Wall',
  '-Wextra',
  '-Wshadow',
  '-Wnon-virtual-dtor',
  '-pedantic',
  '-Wold-style-cast',
  '-Wcast-align',
  '-Wunused',
  '-Woverloaded-virtual',
  '-Wpedantic',
  '-Wconversion',
  '-Wsign-conversion',
  '-Wmisleading-indentation',
  '-Wduplicated-cond',
  '-Wduplicated-branches',
  '-Wlogical-op',
  '-Wnull-dereference',
  '-Wuseless-cast',
  '-Wdouble-promotion',
  '-Wformat=2',
  # '-Wlifetime',
  '-Wimplicit-fallthrough',
  # '-Werror',
  '-fno-exceptions',
  '-fmax-errors=1',
  language: ['cpp', 'c'],
)

if get_option('debug')
  add_global_arguments('-DDEBUG', '-g3', '-O0', language: ['cpp', 'c'])
endif

cpp = meson.get_compiler('cpp')
cc = meson.get_compiler('c')

cmake = import('cmake')

fxtui_cmake = cmake.subproject('fxtui')

fxtui_screen = fxtui_cmake.dependency('screen')
fxtui_dom = fxtui_cmake.dependency('dom')
fxtui_component = fxtui_cmake.dependency('component')

executable('chip8-emulator',
        include_directories: [
                'src/'
        ],
    sources: [
        'src/main.cpp'
    ],
    dependencies: [fxtui_screen, fxtui_dom, fxtui_component]
)
