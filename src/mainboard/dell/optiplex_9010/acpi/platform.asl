Method(_WAK,1)
{
	Return(Package(){0,0})
}

Method(_PTS,1)
{
}

Scope (\_SB)
{
	Device (PWRB)
	{
		Name (_HID, EisaId ("PNP0C0C"))
		Name (_UID, 0xAA)
		Name (_STA, 0x0B)

		Name (_PRW, Package() { 8, 3})
	}
}
