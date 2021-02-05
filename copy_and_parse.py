import os, sys
import string
import shutil
import re
import subprocess

def check_directory_sanity(directory):
    if not os.path.exists(directory):
        raise ValueError("input directory '" + directory + "' does not exist")
    if not os.path.isdir(directory):
        raise ValueError("path '" + directory + "' is no directory")
    return None

def get_commandline_args():
    if len(sys.argv) < 2:
        raise ValueError("expected two commandline arguments:\n\t/path/to/source/directory\n\t/path/to/target/directory")
    input_directory = sys.argv[1]
    target_directory = sys.argv[2]
    return input_directory, target_directory

def get_files_in_directory(directory):
    check_directory_sanity(directory)
    walk_result = os.walk(directory)
    files = []
    for dir_, _, dir_files in walk_result:
        for dir_file in dir_files:
            files.append(dir_ + os.path.sep + dir_file)
    return files

def get_subdirs_in_directory(directory):
    check_directory_sanity(directory)
    walk_result = os.walk(directory)
    dirs = []
    for dir_, subdirs_, _ in walk_result:
        for subdir_ in subdirs_:
            dirs.append(dir_ + os.path.sep + subdir_)
    return dirs

def transform_dirname(object_name, old_dir, new_dir):
    return object_name.replace(old_dir, new_dir, 1)

class FileReplacement(object):
    def __init__(self, filename, old_dir, new_dir):
        self.oldFile = filename
        self.newFile = transform_dirname(filename, old_dir, new_dir)
        return None

def prepare_new_directories(old_dir, new_dir):
    new_dirs = [transform_dirname(i, old_dir, new_dir) for i in get_subdirs_in_directory(old_dir)]
    sorted_dirs = sorted(new_dirs, key = lambda x : len(x))
    for path in sorted_dirs:
        if not os.path.exists(path):
            os.mkdir(path)
    return None

def has_to_be_parsed(filename):
    return (filename[-4:] == ".cpp" or filename[-2:] == ".h") and re.search("source", filename) and not re.search("libraries", filename)

def copy_files(fileinfos):
    #for fileinfo in fileinfos:
    #    if not os.path.exists(fileinfo.newFile):
    #        shutil.copy(fileinfo.oldFile, fileinfo.newFile)
    return

def parse_files(fileinfos):
    program = "./double_to_float"
    for fileinfo in fileinfos:
        proc = subprocess.Popen([program, fileinfo.oldFile, fileinfo.newFile], stdout = subprocess.PIPE, stderr = subprocess.PIPE)

        stdout, stderr = proc.communicate()
        stdout_str = stdout.decode("utf-8")
        stderr_str = stderr.decode("utf-8")

        #if stdout_str:
        #    raise BaseException("file: " + fileinfo.oldFile + "\nprogram should run quietly, got standard output: ", stdout_str)
        if stderr_str:
            raise BaseException("file: " + fileinfo.oldFile + "\nprogram should run quietly, got standard error: ", stderr_str)
    return None

def transform_files():
    # prepare new directories
    input_directory, output_directory = get_commandline_args()
    prepare_new_directories(input_directory, output_directory)
    transformation_info = [FileReplacement(i, input_directory, output_directory) for i in get_files_in_directory(input_directory)]
    files_to_copy = [i for i in transformation_info if not has_to_be_parsed(i.oldFile)]
    files_to_parse = [i for i in transformation_info if has_to_be_parsed(i.newFile)]
    copy_files(files_to_copy)
    parse_files(files_to_parse)
    return None

transform_files()

#files = get_files_in_directory(input_directory)
#check_directory_sanity(output_directory)
#for item in transformation_info:
#    print(item.newFile[-3:])
