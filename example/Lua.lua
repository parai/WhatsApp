require("autosar")
require("math")
require("os")
function wait(time)
  pre = os.clock()
  
  now = os.clock()
  
  while((now-pre)<time) do
    now = os.clock()
  end
end

function OsTick()
  print "Test for Callout"
end

function main()
    print "Hello World!"
    print "Welcome to arLua, hope better AUTOSAR!"
    print("sin(pi/2)=" , math.sin(math.pi/2))
    while true do
      autosar.Can_Write(0,0x100,{0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55})
      wait(1)
    end
end

main()
