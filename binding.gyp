{
    "targets": [
        {
            "target_name": "glfw",
            "sources": ["src/module.cc", "src/glfw.cc"],
            "include_dirs":[
                "dep"
            ],
            "link_settings":{
                "libraries": [
                    "-lglfw"
                ],
                "library_dirs":[
                    "<(module_root_dir)/dep"
                ]
            }
        },
        {
            "target_name": "copy_binary",
            "type": "none",
            "dependencies": ["glfw"],
            "copies":[{
                "destination": "<(module_root_dir)/lib",
                "files": ["<(module_root_dir)/build/release/glfw.node"]
            }]
        }
    ]
}
