cmake_minimum_required(VERSION 3.5.0)
project(ExamManager VERSION 0.1.0 LANGUAGES C)
aux_source_directory(. ALL)
add_executable(ExamManager main.c list_note.c Control.c)