#!/usr/bin/ruby

$pat = ARGV

f = open($pat[0],"r");
fout = open($pat[1],"w");

cnt = 0;

fout.printf("\t");

while(c = f.getc())

    fout.printf("0x%02x,",c);

    if ((cnt+1) % 8 == 0) then
        fout.printf("\n\t");
    end
    
    cnt = cnt + 1;
end

fout.printf("\n\t");
f.close;
fout.close;

printf("Finished\n");
