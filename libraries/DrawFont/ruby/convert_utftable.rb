file = "JIS_X_0208.txt"

table = Hash::new

f = File::open(file,"r")
while (l = f.gets)
  if l =~ /^0x([0-9A-F]{4}).0x([0-9A-F]{4})\r\n$/ then
    code_jis = $1.hex
    code_utf16 = $2.hex
    table[code_utf16] = code_jis
  end
end

f.close

(0..65535).each { |utf16|
  if table.has_key?(utf16) == true then
    printf("\t0x%04X,\t\t// 0x%04X\n",table[utf16],utf16)
  else
    printf("\t0x0000,\t\t// 0x%04X (dummy)\n",utf16)
  end
}
