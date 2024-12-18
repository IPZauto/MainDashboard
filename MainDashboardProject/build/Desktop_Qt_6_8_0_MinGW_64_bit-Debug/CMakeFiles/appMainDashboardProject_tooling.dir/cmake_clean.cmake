file(REMOVE_RECURSE
  "MainDashboardProject/Main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/appMainDashboardProject_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
