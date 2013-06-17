
cmake_minimum_required(VERSION 2.8)	 # Проверка версии CMake.
                                        # Если версия установленой программы
                                        # старее указаной, произайдёт аварийный выход.

project(treemodel)			# Название проекта
find_package(Qt4 REQUIRED)

set(SOURCE_LIB treeitem.cpp  treemodel.cpp)
set(HEADER_LIB treeitem.h  treemodel.h)

QT4_WRAP_CPP(HEADERS_MOC ${HEADER_LIB})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

add_library(treemodelS STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo
add_library(treemodel SHARED ${SOURCE_LIB})	# Создание динамической библиотеки с именем foo

set_target_properties(treemodel  PROPERTIES
	  VERSION 1.0.0
	  SOVERSION 1.0
	)
	
INSTALL(TARGETS treemodelS treemodel
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

INSTALL(FILES ${HEADER_LIB} 
	DESTINATION include)
