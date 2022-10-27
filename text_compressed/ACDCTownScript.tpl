@archive ACDCTownScript
@size 2

script 0 mmbn6 {
	msgOpen
	"Making PVP Save!"
  itemGiveAllChips
	callGiveAllNaviCustPrograms
	startGiveFolder
		slot = 1
		folder = 1
	keyWait
		any = false
	end
}

script 1 mmbn6 {
  flagSet
		flag = 0x403
  end
}
