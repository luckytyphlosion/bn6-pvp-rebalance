@archive ACDCTownScript
@size 12

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
  mugshotShow
    mugshot = 0x45

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
    left = 1
    right = 1
    up = 2
    down = 2
  space
    count = 1
  "FrameData"

  option // 1
    brackets = 0
    left = 0
    right = 0
    up = 2
    down = 2
  space
    count = 1
  "ElecDodge\n"

  option // 2
    brackets = 0
    left = 2
    right = 2
    up = 0
    down = 0
  space
    count = 1
  "BDTDodge"

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
      jump = 5,
      jump = continue
    ]
  clearMsg

  soundDisableTextSFX
  soundPlay
    track = 104
  soundEnableTextSFX

  storeGlobal
    global = 0
    value = 0xff
  storeGlobal
    global = 1
    value = 1
  end
}

script 3 mmbn6 {
  soundDisableTextSFX
  soundPlay
    track = 386
  soundEnableTextSFX

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
  soundDisableTextSFX
  soundPlay
    track = 386
  soundEnableTextSFX

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

script 5 mmbn6 {
  soundDisableTextSFX
  soundPlay
    track = 386
  soundEnableTextSFX

  storeGlobal
    global = 0
    value = 2

  """
  Chose BDT
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

script 6 mmbn6 {
  end
}

script 7 mmbn6 {
  end
}

script 8 mmbn6 {
  end
}

script 9 mmbn6 {
  end
}

script 10 mmbn6 {
  msgOpen
  mugshotShow
    mugshot = 0x3e

  """
  Enable chip lockout
  frames?
  """
  keyWait
    any = false
  clearMsg

  textSpeed
    delay = 0

  positionOptionHorizontal
    width = 7
  option
    brackets = 0
    left = 1
    right = 1
    up = 0
    down = 0
  space
    count = 1
  " Yes  "
  option
    brackets = 0
    left = 0
    right = 0
    up = 1
    down = 1
  space
    count = 1
  " No"

  textSpeed
    delay = 2

  select
    default = 0
    BSeparate = false
    disableB = false
    clear = false
    targets = [
      jump = 11,
      jump = continue,
      jump = 11
    ]
  clearMsg
  soundDisableTextSFX
  soundPlay
    track = 104
  soundEnableTextSFX

  """
  Chip lockout frames
  disabled.
  """
  keyWait
    any = false
  flagClear
    flag = 0x406
  end
}

script 11 mmbn6 {
  clearMsg

  soundDisableTextSFX
  soundPlay
    track = 386
  soundEnableTextSFX

  """
  Chip lockout frames
  enabled!
  """
  keyWait
    any = false
  clearMsg
  flagSet
    flag = 0x406
  end
}

