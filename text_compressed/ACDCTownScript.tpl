@archive ACDCTownScript
@size 5

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

/*
0 1 2 3
4 5 6
7 8 9
*/

script 2 mmbn6 {
  flagSet
    flag = 0x404
  
  waitFlag
    flag = 0x405

  flagClear
    flag = 0x405

  msgOpen
  """
  Choose training
  mode option!
  """
  keyWait
    any = false
  clearMsg

  textSpeed
    delay = 0

  option // 0
    brackets = 0
    left = 3
    right = 1
    up = 0
    down = 0
  space
    count = 1
  "FrameData"

  option // 1
    brackets = 0
    left = 0
    right = 0
    up = 1
    down = 1
  space
    count = 1
  "ElecDodge"

	textSpeed
		delay = 2

  soundDisableChoiceSFX
	select
		default = 0
		BSeparate = true
		disableB = false
		clear = false
		targets = [
			jump = 3,
			jump = 4,
      jump = continue
		]
  clearMsg
  storeGlobal
    global = 0
    value = 0xff
  storeGlobal
    global = 1
    value = 1
  end
}

script 3 mmbn6 {
  storeGlobal
    global = 0
    value = 0

  """
  Chose Frame Data
  mode!
  """
  keyWait
    any = false
  clearMsg
  storeGlobal
    global = 1
    value = 1
  end
}

script 4 mmbn6 {
  storeGlobal
    global = 0
    value = 1

  """
  Chose ElecCross
  dodging mode!
  """
  keyWait
    any = false
  clearMsg
  storeGlobal
    global = 1
    value = 1
  end
}
