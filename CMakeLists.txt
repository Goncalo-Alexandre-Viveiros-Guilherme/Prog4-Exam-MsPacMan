cmake_minimum_required(VERSION 3.26)
project(Minigin)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
  set(TARGET_NAME minigin_web)
  set(TARGET_PARAM )
else()
  set(TARGET_NAME minigin)
  set(TARGET_PARAM WIN32)
endif() 

# list source files here
add_executable(${TARGET_NAME} ${TARGET_PARAM}
    Minigin/Main.cpp
    Minigin/Components/HealthComponent.cpp 
    Minigin/Components/HealthDisplayComponent.cpp  
    Minigin/Components/PointsComponent.cpp
    Minigin/Components/PointsDisplayComponent.cpp 
    Minigin/GameSource/Achievements.cpp
)

add_library(miniginLib STATIC 
   Minigin/Engine/GameObject.cpp
   Minigin/Engine/Minigin.cpp
   Minigin/Engine/Scene.cpp
   Minigin/Engine/Commands.cpp
   Minigin/Engine/EngineTime.cpp
   Minigin/Engine/Transform.cpp

   
   Minigin/Rendering/Renderer.cpp
   Minigin/Rendering/Texture2D.cpp
   Minigin/Rendering/Font.cpp

   Minigin/Managers/InputManager.cpp
   Minigin/Managers/ResourceManager.cpp
   Minigin/Managers/SceneManager.cpp
 
   Minigin/Components/Component.cpp 
   Minigin/Components/TextComponent.cpp
   Minigin/Components/ImageComponent.cpp
   Minigin/Components/FPSComponent.cpp
   Minigin/Components/RotatorComponent.cpp 
   Minigin/Components/GraphCacheComponent.cpp 
   Minigin/Engine/SteamAchievements.cpp 
   Minigin/Engine/Singleton.h
   Minigin/Engine/Events.h
   Minigin/Engine/EventDispatcher.h
   Minigin/Engine/Minigin.h
   Minigin/Engine/SDLAudio.cpp 
   Minigin/Engine/Audio.h
   Minigin/Engine/NullAudio.h
   Minigin/Engine/ServiceLocator.cpp)
 target_link_libraries(${TARGET_NAME} PUBLIC miniginLib)

# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
target_compile_features(miniginLib PUBLIC cxx_std_20)
# set minigin as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

# add SDL2
if (WIN32)
  FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.30.10-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_GetProperties(SDL2)
  if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
  else()
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
  endif()
  endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.3-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_image)
  if(NOT SDL2_image_POPULATED)
    FetchContent_Populate(SDL2_image)
    set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
  else()
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
  endif()
  endif()

  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.22.0-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_ttf)
  if(NOT sdl2_ttf_POPULATED)
    FetchContent_Populate(SDL2_ttf)
    set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
  else()
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
  endif()
  endif()

  # add SDL2_mixer
FetchContent_Declare(
  SDL2_mixer
  URL https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.8.1-VC.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)
FetchContent_GetProperties(SDL2_mixer)
if(NOT SDL2_mixer_POPULATED)
  FetchContent_Populate(SDL2_mixer)
  set(SDL2_MIXER_INCLUDE_DIR ${sdl2_mixer_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_MIXER_LIBRARIES "${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.lib")
    set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.dll")
  else()
    set(SDL2_MIXER_LIBRARIES "${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.lib")
    set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.dll")
  endif()
endif()

  find_package(VLD CONFIG)

  # set all include directories
  #target_include_directories(${TARGET_NAME} PRIVATE
  target_include_directories(miniginLib PUBLIC
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
  )
  
  # set libraries to link with
  #target_link_libraries(${TARGET_NAME} PUBLIC
  target_link_libraries(miniginLib PUBLIC
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${VLD_LIBRARY}
  )
   
elseif(NOT EMSCRIPTEN)

  FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL2)
  
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_image)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_ttf)

  FetchContent_Declare(
  SDL2_mixer
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
  GIT_TAG release-2.8.1
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  )
  set(SDL2MIXER_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_mixer)

 target_include_directories("${TARGET_NAME}" PUBLIC 
     ${sdl2_SOURCE_DIR}/include
    ${sdl2_image_SOURCE_DIR}/include
    ${sdl2_ttf_SOURCE_DIR}
  )
   target_include_directories(miniginLib PUBLIC 
    ${sdl2_SOURCE_DIR}/include
    ${sdl2_image_SOURCE_DIR}/include
    ${sdl2_ttf_SOURCE_DIR}
    ${sdl2_mixer_SOURCE_DIR}
  )
  target_link_libraries("${TARGET_NAME}" PUBLIC 
     SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf
  )
 target_link_libraries(miniginLib PUBLIC 
    SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer
  )

endif()

# Link XInput for Windows
if(WIN32)
    target_link_libraries("${TARGET_NAME}" PUBLIC Xinput.lib)
    target_link_libraries(miniginLib PUBLIC Xinput.lib)
endif()

# Add custom command to copy DLLs after the build
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_LIBRARY_DLL}  # Copy SDL2.dll
        $<TARGET_FILE_DIR:${TARGET_NAME}>)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_MIXER_LIBRARY_DLL}  # Copy SDL2_mixer.dll
        $<TARGET_FILE_DIR:${TARGET_NAME}>)

############################################################################### ImGui

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.8
)

FetchContent_MakeAvailable(imgui)

# Add ImGui
add_library(imgui_lib STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp    
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

target_link_libraries(miniginLib PUBLIC imgui_lib)
target_include_directories(imgui_lib PUBLIC ${imgui_SOURCE_DIR})
target_include_directories(imgui_lib PUBLIC ${SDL2_INCLUDE_DIR})

FetchContent_Declare(
  implot
  GIT_REPOSITORY https://github.com/epezent/implot.git
  GIT_TAG v0.16
)

FetchContent_MakeAvailable(implot)

#Add Im Plot
add_library(implot_lib STATIC
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp)

target_include_directories(implot_lib PUBLIC ${implot_SOURCE_DIR} ${imgui_SOURCE_DIR})
target_link_libraries(miniginLib PUBLIC implot_lib)
 ########################################################################Imgui
    target_link_libraries(imgui_lib PUBLIC ${SDL2_LIBRARIES})

function(use_steamworks ENGINE_TARGET)
    set(STEAMWORKS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Minigin/3rdParty/steamworks")

    set(STEAMWORKS_INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/Minigin/3rdParty/steamworks/public/steam)
    set(STEAMWORKS_LIB_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/Minigin/3rdParty/steamworks/redistributable_bin)

    set(STEAMWORKS_LIB ${STEAMWORKS_LIB_DIR}/win64/steam_api64.lib)
        
    add_custom_command(
            TARGET ${ENGINE_TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${STEAMWORKS_LIB_DIR}/win64/steam_api64.dll $<TARGET_FILE_DIR:${TARGET_NAME}>)

    target_include_directories(${ENGINE_TARGET} PUBLIC ${STEAMWORKS_INCLUDE_DIR})
    target_link_libraries(${ENGINE_TARGET} PUBLIC ${STEAMWORKS_LIB})

    target_compile_definitions(${ENGINE_TARGET} PUBLIC USE_STEAMWORKS)
endfunction()

use_steamworks(${TARGET_NAME})
use_steamworks(miniginLib)

set(MINIGIN_INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/Minigin/
  ${CMAKE_SOURCE_DIR}/Minigin/Engine/
  ${CMAKE_SOURCE_DIR}/Minigin/GameSource/
  ${CMAKE_SOURCE_DIR}/Minigin/Components/
  ${CMAKE_SOURCE_DIR}/Minigin/Managers/
  ${CMAKE_SOURCE_DIR}/Minigin/Rendering/
  ${glm_SOURCE_DIR}
)

target_include_directories(miniginLib PRIVATE ${MINIGIN_INCLUDE_DIRS})
target_include_directories(${TARGET_NAME} PRIVATE ${MINIGIN_INCLUDE_DIRS})

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g")
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" -sSDL2_IMAGE_FORMATS=['tga','png']")

  # work around https://github.com/emscripten-core/emscripten/issues/11513
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -fno-stack-protector")

  # Use the Emscripten toolchain
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EmscriptenToolchain.cmake)

  # Additional settings for Emscripten build
  set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )

  # Have emscripten generate a html page too.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  
elseif(WIN32)
  set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")

  # add post build commands
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
endif()
