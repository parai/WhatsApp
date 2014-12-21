require("autosar")
require("math")
function main()
    print "Hello World!"
    print "Welcome to arLua, hope better AUTOSAR!"
    print("sin(pi/2)=" , math.sin(math.pi/2))
    autosar.Can_Write(0,0x100,{0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55})
end

main()
