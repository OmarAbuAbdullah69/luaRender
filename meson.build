project('luaRender', 'cpp')

# Run a shell command to find all .cpp files
cpp_sources = run_command(
  'find', meson.current_source_dir(), '-name', '*.cpp', check:true,
).stdout().split()

inc_dir = include_directories('./include')

compile_args = []
if get_option('build_type') == 'debug'
  add_project_arguments('-DDEB_BUILD', language:'cpp')
  compile_args += ['-g', '-ggdb']
elif  get_option('build_type') == 'release'
  add_project_arguments('-DREL_BUILD', language:'cpp')
  compile_args += ['-o3']
endif

executable('luaRender', cpp_sources,
  include_directories: inc_dir,
  cpp_args: compile_args,
  )
