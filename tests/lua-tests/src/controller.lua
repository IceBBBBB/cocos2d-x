-- jit off
local jit = require("jit")
jit.off()
-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)
	
require "mainMenu"
----------------


-- run
local scene = cc.Scene:create()
scene:addChild(CreateTestMenu())
cc.Director:getInstance():runWithScene(scene)
