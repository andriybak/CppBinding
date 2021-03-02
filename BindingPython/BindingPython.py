
import ctypes
import pathlib
from argparse import ArgumentParser
import sys


#globals for ease of use
libname = "../CppBinding.dll"
map_lib = None


class StyleOptions:
    def __init__(self):
        create_style_options_wrap = map_lib.CreateStyleOptionsInstance
        create_style_options_wrap.restype = ctypes.c_void_p
        self.style_options_instance = ctypes.c_void_p(create_style_options_wrap())

    def __del__(self):
        map_lib.DestroyStyleOptionsInstance(self.style_options_instance)

    def set_style_from_url(self, style: str):
        bytes_url_style = style.encode('utf-8')

        set_style_with_url = map_lib.CreateStyleWithStyleURL
        set_style_with_url.restype = ctypes.c_void_p
        set_style_with_url.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.style_options_instance = ctypes.c_void_p(
            set_style_with_url(self.style_options_instance, bytes_url_style))


class StyleMap:
    def __init__(self):
        create_map_func = map_lib.CreateMapInstance
        create_map_func.restype = ctypes.c_void_p
        self.style_map_instance = ctypes.c_void_p(create_map_func())

    def __del__(self):
        map_lib.DestroyMapInstance(self.style_map_instance)

    def SetStyle(self, style: StyleOptions):
        set_map_style = map_lib.SetMapStyle
        set_map_style.restype = ctypes.c_void_p
        set_map_style.argtypes = [ctypes.c_void_p, ctypes.c_void_p]

        self.style_map_instance = ctypes.c_void_p(set_map_style(self.style_map_instance, style.style_options_instance))

    def RenderMap(self, render_func):
        #function should be void with no params
        render_func_wrap = ctypes.CFUNCTYPE(None)
        render_function = render_func_wrap(render_func)

        try:
            map_lib.RenderMap(self.style_map_instance, render_function)
        except OSError as err:
            runtime_error_code = 22
            if err.args[0] == runtime_error_code:
                print('no valid style is set!')
            else:
                print('Unexpected error')


def _render_func():
    print('map rendered in Python!\n')


if __name__ == "__main__":
    parser = ArgumentParser(
        description='Python implementation.To run you can either specify a\
                     path to the compiled c++ dll file as input argument and\
                     the style string if you want something customized.')
    parser.add_argument(
        '-l', '--lib', help='Full path to the .dll file with functionality', default=libname, required=False)
    parser.add_argument('-s', '--style', help='style string url to use for map',
                        default='https://www.test.com', required=False)

    args = parser.parse_args()
    libname = args.lib
    style_url = args.style

    map_lib = ctypes.cdll.LoadLibrary(libname)

    style_options = StyleOptions()
    style_options.set_style_from_url('www.test.com')

    style_map = StyleMap()
    style_map.SetStyle(style_options)
    style_map.RenderMap(_render_func)
