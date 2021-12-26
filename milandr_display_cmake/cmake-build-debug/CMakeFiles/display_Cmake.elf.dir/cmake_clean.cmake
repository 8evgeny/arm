file(REMOVE_RECURSE
  "display_Cmake.elf"
  "display_Cmake.elf.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/display_Cmake.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
