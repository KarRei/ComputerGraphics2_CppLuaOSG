function read(barriersDef)
 
  file = assert(io.open(barriersDef, "r"))
  for line in file:lines() do
    line = string.gsub(line, "%s*#.*", "")  -- delete comments
    line = string.gsub(line, "^%s+", "")    -- leading space
    line = string.gsub(line, "%s*;%s*$", "")    -- trailing spaces, semi

    line = string.gsub(line, "%s", "")
    local _, _,a, b, c, d, e, f = string.find(line, "%((-?%d+%.?%d*),(-?%d+%.?%d*),(-?%d+%.?%d*),(-?%d+%.?%d*),(-?%d+%.?%d*),(-?%d+%.?%d*)%)")

    addBarrier(a, b, c, d, e, f);
--print(a);
--print(b);
--print(c);
--print(d);
--print(e);
--print(f);
  end
end
