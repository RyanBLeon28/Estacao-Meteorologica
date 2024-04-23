(kicad_sch
	(version 20231120)
	(generator "eeschema")
	(generator_version "8.0")
	(uuid "8b2fb0b9-aa0a-43c0-9ebf-6130403d9509")
	(paper "A4")
	(title_block
		(title "AS5600 Breakout")
		(date "2019-03-09")
		(rev "1")
		(company "Kane Stoboi")
	)
	(lib_symbols
		(symbol "AS5600:AS5600"
			(pin_names
				(offset 1.016)
			)
			(exclude_from_sim no)
			(in_bom yes)
			(on_board yes)
			(property "Reference" "U"
				(at -1.27 7.62 0)
				(effects
					(font
						(size 1.524 1.524)
					)
				)
			)
			(property "Value" "AS5600"
				(at 3.81 -7.62 0)
				(effects
					(font
						(size 1.524 1.524)
					)
				)
			)
			(property "Footprint" ""
				(at 0 0 0)
				(effects
					(font
						(size 1.524 1.524)
					)
					(hide yes)
				)
			)
			(property "Datasheet" ""
				(at 0 0 0)
				(effects
					(font
						(size 1.524 1.524)
					)
					(hide yes)
				)
			)
			(property "Description" ""
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(symbol "AS5600_0_1"
				(polyline
					(pts
						(xy -3.81 6.35) (xy -3.81 -6.35) (xy 11.43 -6.35) (xy 11.43 6.35) (xy -3.81 6.35)
					)
					(stroke
						(width 0)
						(type solid)
					)
					(fill
						(type none)
					)
				)
			)
			(symbol "AS5600_1_1"
				(pin input line
					(at -8.89 3.81 0)
					(length 5.08)
					(name "VDD_5V"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "1"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at -8.89 1.27 0)
					(length 5.08)
					(name "VDD_3V"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "2"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at -8.89 -1.27 0)
					(length 5.08)
					(name "OUT"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "3"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at -8.89 -3.81 0)
					(length 5.08)
					(name "GND"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "4"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at 16.51 -3.81 180)
					(length 5.08)
					(name "PGO"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "5"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at 16.51 -1.27 180)
					(length 5.08)
					(name "SDA"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "6"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at 16.51 1.27 180)
					(length 5.08)
					(name "SCL"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "7"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin input line
					(at 16.51 3.81 180)
					(length 5.08)
					(name "DIR"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "8"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
			)
		)
		(symbol "Device:C"
			(pin_numbers hide)
			(pin_names
				(offset 0.254)
			)
			(exclude_from_sim no)
			(in_bom yes)
			(on_board yes)
			(property "Reference" "C"
				(at 0.635 2.54 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(justify left)
				)
			)
			(property "Value" "C"
				(at 0.635 -2.54 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(justify left)
				)
			)
			(property "Footprint" ""
				(at 0.9652 -3.81 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Datasheet" "~"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Description" "Unpolarized capacitor"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "ki_keywords" "cap capacitor"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "ki_fp_filters" "C_*"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(symbol "C_0_1"
				(polyline
					(pts
						(xy -2.032 -0.762) (xy 2.032 -0.762)
					)
					(stroke
						(width 0.508)
						(type default)
					)
					(fill
						(type none)
					)
				)
				(polyline
					(pts
						(xy -2.032 0.762) (xy 2.032 0.762)
					)
					(stroke
						(width 0.508)
						(type default)
					)
					(fill
						(type none)
					)
				)
			)
			(symbol "C_1_1"
				(pin passive line
					(at 0 3.81 270)
					(length 2.794)
					(name "~"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "1"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin passive line
					(at 0 -3.81 90)
					(length 2.794)
					(name "~"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "2"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
			)
		)
		(symbol "Device:R"
			(pin_numbers hide)
			(pin_names
				(offset 0)
			)
			(exclude_from_sim no)
			(in_bom yes)
			(on_board yes)
			(property "Reference" "R"
				(at 2.032 0 90)
				(effects
					(font
						(size 1.27 1.27)
					)
				)
			)
			(property "Value" "R"
				(at 0 0 90)
				(effects
					(font
						(size 1.27 1.27)
					)
				)
			)
			(property "Footprint" ""
				(at -1.778 0 90)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Datasheet" "~"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Description" "Resistor"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "ki_keywords" "R res resistor"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "ki_fp_filters" "R_*"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(symbol "R_0_1"
				(rectangle
					(start -1.016 -2.54)
					(end 1.016 2.54)
					(stroke
						(width 0.254)
						(type default)
					)
					(fill
						(type none)
					)
				)
			)
			(symbol "R_1_1"
				(pin passive line
					(at 0 3.81 270)
					(length 1.27)
					(name "~"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "1"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
				(pin passive line
					(at 0 -3.81 90)
					(length 1.27)
					(name "~"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "2"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
			)
		)
		(symbol "power:GND"
			(power)
			(pin_numbers hide)
			(pin_names
				(offset 0) hide)
			(exclude_from_sim no)
			(in_bom yes)
			(on_board yes)
			(property "Reference" "#PWR"
				(at 0 -6.35 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Value" "GND"
				(at 0 -3.81 0)
				(effects
					(font
						(size 1.27 1.27)
					)
				)
			)
			(property "Footprint" ""
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Datasheet" ""
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "Description" "Power symbol creates a global label with name \"GND\" , ground"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(property "ki_keywords" "global power"
				(at 0 0 0)
				(effects
					(font
						(size 1.27 1.27)
					)
					(hide yes)
				)
			)
			(symbol "GND_0_1"
				(polyline
					(pts
						(xy 0 0) (xy 0 -1.27) (xy 1.27 -1.27) (xy 0 -2.54) (xy -1.27 -1.27) (xy 0 -1.27)
					)
					(stroke
						(width 0)
						(type default)
					)
					(fill
						(type none)
					)
				)
			)
			(symbol "GND_1_1"
				(pin power_in line
					(at 0 0 270)
					(length 0)
					(name "~"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
					(number "1"
						(effects
							(font
								(size 1.27 1.27)
							)
						)
					)
				)
			)
		)
	)
	(junction
		(at 166.37 110.49)
		(diameter 0)
		(color 0 0 0 0)
		(uuid "37493ae8-68af-4c5e-8b21-4bc21a42594d")
	)
	(junction
		(at 128.27 105.41)
		(diameter 0)
		(color 0 0 0 0)
		(uuid "4fd83187-3bbc-4d1e-9944-771bdf1d1d9a")
	)
	(junction
		(at 166.37 107.95)
		(diameter 0)
		(color 0 0 0 0)
		(uuid "bd83c6a9-9acb-4e5e-9993-72b8612ff971")
	)
	(junction
		(at 119.38 107.95)
		(diameter 0)
		(color 0 0 0 0)
		(uuid "d2d33afb-89a4-4a1e-aabf-77fc42de74b6")
	)
	(junction
		(at 157.48 105.41)
		(diameter 0)
		(color 0 0 0 0)
		(uuid "e188829e-d147-4651-bd5c-2598531f160d")
	)
	(junction
		(at 134.62 68.58)
		(diameter 0)
		(color 0 0 0 0)
		(uuid "ff62018f-e009-4e11-b3a4-12ef5c188f81")
	)
	(wire
		(pts
			(xy 132.08 68.58) (xy 134.62 68.58)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "02ad5a30-ea29-4db0-ba57-e499f28f1df5")
	)
	(wire
		(pts
			(xy 166.37 110.49) (xy 156.21 110.49)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "038d8189-04a6-403d-a403-c0256db57aea")
	)
	(wire
		(pts
			(xy 157.48 96.52) (xy 157.48 97.79)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "0856bc39-b4d8-465b-aea8-7941fe9b45d5")
	)
	(wire
		(pts
			(xy 179.07 104.14) (xy 179.07 114.3)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "0dabe1e9-c0b7-479d-86b3-f2b2409089cb")
	)
	(wire
		(pts
			(xy 157.48 105.41) (xy 158.75 105.41)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "262a28f0-fa16-45d6-b9b7-bfdb7a201977")
	)
	(wire
		(pts
			(xy 175.26 74.93) (xy 175.26 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "2b69a9dd-e852-43b8-883a-fd0b093edb27")
	)
	(wire
		(pts
			(xy 173.99 104.14) (xy 179.07 104.14)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "34e23fb1-099f-43e5-82a7-e6ee5440b432")
	)
	(wire
		(pts
			(xy 119.38 99.06) (xy 119.38 97.79)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "3c6c0d6f-6587-423e-a9fd-cda20392ae51")
	)
	(wire
		(pts
			(xy 128.27 113.03) (xy 128.27 114.3)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "3dbfa136-d67d-401b-a82b-68d0318d4840")
	)
	(wire
		(pts
			(xy 128.27 110.49) (xy 130.81 110.49)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "419b4042-d4fa-4d79-b1f2-06a5025ca358")
	)
	(wire
		(pts
			(xy 128.27 95.25) (xy 128.27 96.52)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "47da8573-6c0f-40da-94f8-a573e36d9f95")
	)
	(wire
		(pts
			(xy 128.27 105.41) (xy 130.81 105.41)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "4b9c34eb-e229-4ff5-87d2-0494fb570abf")
	)
	(wire
		(pts
			(xy 160.02 74.93) (xy 160.02 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "500aebac-91a6-438a-8958-5f5b3bc5ce05")
	)
	(wire
		(pts
			(xy 166.37 107.95) (xy 170.18 107.95)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "542705b0-706b-4a5d-be7e-b4fd4c94538b")
	)
	(wire
		(pts
			(xy 127 105.41) (xy 128.27 105.41)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "5613fd8a-be5c-4384-8424-56f3c240e35c")
	)
	(wire
		(pts
			(xy 165.1 74.93) (xy 165.1 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "58e2e0df-d896-4a8f-8ffc-cc7ad6f846b7")
	)
	(wire
		(pts
			(xy 134.62 68.58) (xy 143.51 68.58)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "6573a085-a931-453f-ba03-f98297801841")
	)
	(wire
		(pts
			(xy 124.46 68.58) (xy 123.19 68.58)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "66141c80-a6d2-4456-8cd4-5ec8a687143f")
	)
	(wire
		(pts
			(xy 162.56 74.93) (xy 162.56 78.74)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "6ce0550e-1db2-4f31-8cee-534286c788f0")
	)
	(wire
		(pts
			(xy 156.21 107.95) (xy 166.37 107.95)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "6eaa6b48-5237-4307-9468-91706e566a98")
	)
	(wire
		(pts
			(xy 172.72 74.93) (xy 172.72 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "74f2b095-56f3-4d41-9bed-90e8b435fbd3")
	)
	(wire
		(pts
			(xy 156.21 113.03) (xy 158.75 113.03)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "76165287-fe90-435f-8e60-533ac7f6967f")
	)
	(wire
		(pts
			(xy 116.84 107.95) (xy 119.38 107.95)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "81007387-4167-45a5-a575-40c3bcb111a1")
	)
	(wire
		(pts
			(xy 119.38 107.95) (xy 119.38 106.68)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "bd14defb-c0ae-48b4-bc7c-7e73e17c3c28")
	)
	(wire
		(pts
			(xy 173.99 114.3) (xy 179.07 114.3)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "bf048202-43e2-446c-95f5-97f9e123acaa")
	)
	(wire
		(pts
			(xy 134.62 77.47) (xy 134.62 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "bff24951-196b-42db-94fd-42a91a18d35a")
	)
	(wire
		(pts
			(xy 170.18 74.93) (xy 170.18 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "c2cca846-a266-469e-b0ba-6135922ca885")
	)
	(wire
		(pts
			(xy 167.64 74.93) (xy 167.64 76.2)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "c6c83d6b-6083-44f0-b8b7-ade75d822569")
	)
	(wire
		(pts
			(xy 170.18 110.49) (xy 166.37 110.49)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "c9596a5d-d469-46eb-9e7a-12c1e19112a3")
	)
	(wire
		(pts
			(xy 156.21 105.41) (xy 157.48 105.41)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "cff78c58-5b35-478b-b865-105eb73773b7")
	)
	(wire
		(pts
			(xy 130.81 113.03) (xy 128.27 113.03)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "d5f35501-fb8f-4e9e-a25f-a68eaa060bfc")
	)
	(wire
		(pts
			(xy 166.37 110.49) (xy 166.37 114.3)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "e32b5e41-44f7-4e7b-a863-8a7179da269e")
	)
	(wire
		(pts
			(xy 119.38 107.95) (xy 130.81 107.95)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "e6c27850-2a0e-4ff1-94ce-3612f9eab370")
	)
	(wire
		(pts
			(xy 166.37 104.14) (xy 166.37 107.95)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "ea19c7cb-e1d9-4619-9b6f-7a85aa107f9b")
	)
	(wire
		(pts
			(xy 128.27 105.41) (xy 128.27 104.14)
		)
		(stroke
			(width 0)
			(type default)
		)
		(uuid "fde071bf-ee28-4963-bd53-1c926cd41e1b")
	)
	(global_label "SDA"
		(shape input)
		(at 172.72 76.2 270)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "05004990-2430-4fd9-8b59-5c447efd9ac6")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 172.72 76.2 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "SDA"
		(shape input)
		(at 170.18 110.49 0)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify left)
		)
		(uuid "13dbeb03-d285-4d79-a0f9-08d3d64ec346")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 170.18 110.49 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "SCL"
		(shape input)
		(at 170.18 76.2 270)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "189ec44c-ea25-41ec-a2fd-225307678bda")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 170.18 76.2 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "OUT"
		(shape input)
		(at 128.27 110.49 180)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "195db958-f06b-486a-9cd8-2819e2c734fa")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 128.27 110.49 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "VIN"
		(shape input)
		(at 160.02 76.2 270)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "24ed6f5c-3384-48fb-b29a-d4e584455ceb")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 160.02 76.2 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "SCL"
		(shape input)
		(at 170.18 107.95 0)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify left)
		)
		(uuid "4d4445a1-1d41-4e7b-9539-a5f00d525e80")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 170.18 107.95 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "PGO"
		(shape input)
		(at 175.26 76.2 270)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "5789ffd2-7ba7-4547-bd1d-452967968766")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 175.26 76.2 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "DIR"
		(shape input)
		(at 167.64 76.2 270)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "5b88a5ff-04da-425a-b873-da868432bc18")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 167.64 76.2 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "PGO"
		(shape input)
		(at 158.75 113.03 0)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify left)
		)
		(uuid "7b49c60e-42b0-4128-829c-a61b0b69bbb4")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 158.75 113.03 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "5V"
		(shape input)
		(at 179.07 109.22 0)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify left)
		)
		(uuid "8988531d-8a96-4285-ab05-faef39df19ba")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 179.07 109.22 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "5V"
		(shape input)
		(at 143.51 68.58 0)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify left)
		)
		(uuid "934ae597-faa1-4eb8-a173-873406e21932")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 143.51 68.58 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "DIR"
		(shape input)
		(at 158.75 105.41 0)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify left)
		)
		(uuid "a28abe0d-effb-46ba-93bd-8522d10ef2ae")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 158.75 105.41 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "OUT"
		(shape input)
		(at 165.1 76.2 270)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "baee22d4-d1af-486e-bda1-93040d91b747")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 165.1 76.2 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "3.3V"
		(shape input)
		(at 116.84 107.95 180)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "d004e684-cf9d-446d-8750-2f88142e4046")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 116.84 107.95 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "VIN"
		(shape input)
		(at 123.19 68.58 180)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "f6de6f27-3c81-4201-b8dd-50a76b51a30f")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 123.19 68.58 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(global_label "5V"
		(shape input)
		(at 127 105.41 180)
		(effects
			(font
				(size 1.143 1.143)
			)
			(justify right)
		)
		(uuid "fff8cc83-0116-4259-9969-413a9d0cc8bc")
		(property "Intersheetrefs" "${INTERSHEET_REFS}"
			(at 127 105.41 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
	)
	(symbol
		(lib_id "AS5600:AS5600")
		(at 139.7 109.22 0)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b77739f")
		(property "Reference" "U1"
			(at 138.43 101.6 0)
			(effects
				(font
					(size 1.524 1.524)
				)
			)
		)
		(property "Value" "AS5600"
			(at 143.51 116.84 0)
			(effects
				(font
					(size 1.524 1.524)
				)
			)
		)
		(property "Footprint" "SMD_Packages:SOIC-8-N"
			(at 139.7 109.22 0)
			(effects
				(font
					(size 1.524 1.524)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 139.7 109.22 0)
			(effects
				(font
					(size 1.524 1.524)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 139.7 109.22 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Manufacturer Part Number" "AS5600-ASOM"
			(at 139.7 109.22 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "50d2b80d-affa-4f9f-8224-a15c887a75f0")
		)
		(pin "2"
			(uuid "f24945a4-9c13-4842-9eb0-11d8027082ac")
		)
		(pin "3"
			(uuid "155b764f-12ae-42cd-8f60-87a8c12624d3")
		)
		(pin "4"
			(uuid "d70de50d-73d5-4fd6-bbd8-35a1d34e58d7")
		)
		(pin "5"
			(uuid "591692bc-a6e7-4e45-9f03-512b9fee7c71")
		)
		(pin "6"
			(uuid "b51fe304-63da-4e95-b422-e370fcb3ad0d")
		)
		(pin "7"
			(uuid "74306850-fe94-4047-9aef-6db3bf0963cf")
		)
		(pin "8"
			(uuid "08e9084f-f9a6-498c-97e9-b916d7b12926")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "U1")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:C")
		(at 128.27 100.33 180)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b7775cb")
		(property "Reference" "C2"
			(at 127 97.79 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(justify left)
			)
		)
		(property "Value" "100nF"
			(at 134.62 97.79 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(justify left)
			)
		)
		(property "Footprint" "Capacitors_SMD:C_0805"
			(at 127.3048 96.52 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 128.27 100.33 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 128.27 100.33 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "6450b52b-1748-4cbf-bbcf-9efad0c7f397")
		)
		(pin "2"
			(uuid "ca968cb1-dcc8-4eae-b793-1a2cf08eeb6b")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "C2")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "power:GND")
		(at 128.27 95.25 180)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b777636")
		(property "Reference" "#PWR01"
			(at 128.27 88.9 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Value" "GND"
			(at 128.27 91.44 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" ""
			(at 128.27 95.25 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 128.27 95.25 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 128.27 95.25 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "318705bf-a705-4d7a-b6c0-dae18873f6bb")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "#PWR01")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "power:GND")
		(at 162.56 78.74 0)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b77765c")
		(property "Reference" "#PWR02"
			(at 162.56 85.09 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Value" "GND"
			(at 162.56 82.55 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" ""
			(at 162.56 78.74 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 162.56 78.74 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 162.56 78.74 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "e89493c3-915a-4f54-9fdb-1a52c82120db")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "#PWR02")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:C")
		(at 119.38 102.87 0)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b777736")
		(property "Reference" "C1"
			(at 115.57 100.33 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(justify left)
			)
		)
		(property "Value" "1uF"
			(at 119.38 100.33 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(justify left)
			)
		)
		(property "Footprint" "Capacitors_SMD:C_0805"
			(at 120.3452 106.68 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 119.38 102.87 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 119.38 102.87 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "4d547617-3f0b-4bd2-8649-bf61641a8aba")
		)
		(pin "2"
			(uuid "b2f17f78-9fc5-4f5c-badb-d779eab59c9c")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "C1")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "power:GND")
		(at 119.38 97.79 180)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b77776c")
		(property "Reference" "#PWR03"
			(at 119.38 91.44 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Value" "GND"
			(at 119.38 93.98 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" ""
			(at 119.38 97.79 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 119.38 97.79 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 119.38 97.79 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "d3f54edf-4507-49bc-a3c4-de7ed988c122")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "#PWR03")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "power:GND")
		(at 128.27 114.3 0)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b77778c")
		(property "Reference" "#PWR04"
			(at 128.27 120.65 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Value" "GND"
			(at 128.27 118.11 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" ""
			(at 128.27 114.3 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 128.27 114.3 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 128.27 114.3 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "d5b7a7a7-1b13-4406-a6e7-5d964ceedb9e")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "#PWR04")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:R")
		(at 170.18 104.14 270)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b777c09")
		(property "Reference" "R1"
			(at 170.18 101.6 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Value" "4.7k"
			(at 170.18 104.14 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" "Resistors_SMD:R_0805"
			(at 170.18 102.362 90)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 170.18 104.14 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 170.18 104.14 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "2"
			(uuid "aada9de4-e135-4245-a29c-c5fc48536e0d")
		)
		(pin "1"
			(uuid "b6ff8fe6-b76a-4759-942b-f6c53571825c")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "R1")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:R")
		(at 170.18 114.3 270)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b777c78")
		(property "Reference" "R2"
			(at 170.18 116.332 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Value" "4.7k"
			(at 170.18 114.3 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" "Resistors_SMD:R_0805"
			(at 170.18 112.522 90)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 170.18 114.3 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 170.18 114.3 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "2"
			(uuid "8f7f4dbc-c120-4aae-871c-705925d45386")
		)
		(pin "1"
			(uuid "2a26e0d7-4764-40c8-9870-b11190122ffa")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "R2")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Connector:Conn_01x07_Male")
		(at 167.64 69.85 90)
		(mirror x)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005b78a669")
		(property "Reference" "J1"
			(at 158.75 72.39 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Value" "Conn_01x07"
			(at 171.45 72.39 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" "Pin_Headers:Pin_Header_Angled_1x07_Pitch2.54mm"
			(at 167.64 69.85 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 167.64 69.85 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 167.64 69.85 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "J1")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:R")
		(at 157.48 101.6 0)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005c26f27d")
		(property "Reference" "R3"
			(at 160.02 101.6 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Value" "4.7k"
			(at 157.48 101.6 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" "Resistors_SMD:R_0805"
			(at 155.702 101.6 90)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 157.48 101.6 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 157.48 101.6 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "ea8f225f-f839-498d-a68f-375bebc32171")
		)
		(pin "2"
			(uuid "7727edaa-e0dd-4c7b-86a4-89cb1291bbce")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "R3")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "power:GND")
		(at 157.48 96.52 180)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005c26f2b4")
		(property "Reference" "#PWR05"
			(at 157.48 90.17 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Value" "GND"
			(at 157.48 92.71 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" ""
			(at 157.48 96.52 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 157.48 96.52 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 157.48 96.52 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "5a15e1c5-dc75-43d0-b35d-408c0f82c7d1")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "#PWR05")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:C")
		(at 134.62 72.39 180)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005c26f570")
		(property "Reference" "C3"
			(at 137.16 74.93 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(justify left)
			)
		)
		(property "Value" "100uF"
			(at 140.97 69.85 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(justify left)
			)
		)
		(property "Footprint" "Capacitors_SMD:C_1210"
			(at 133.6548 68.58 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 134.62 72.39 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 134.62 72.39 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "1cc01a70-f4e2-4034-be1b-fe0b59245ec6")
		)
		(pin "2"
			(uuid "1dd34a84-1fd0-40a7-bdd2-d07ab53a12fd")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "C3")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "Device:R")
		(at 128.27 68.58 270)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005c26f640")
		(property "Reference" "R4"
			(at 128.27 70.612 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Value" "1.6k"
			(at 128.27 68.58 90)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" "Resistors_SMD:R_0805"
			(at 128.27 66.802 90)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 128.27 68.58 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 128.27 68.58 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "a7a86bfd-61fb-4220-859f-a50d7a96f9ae")
		)
		(pin "2"
			(uuid "9ba7135e-4ef5-46c9-99dd-505fbda79fea")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "R4")
					(unit 1)
				)
			)
		)
	)
	(symbol
		(lib_id "power:GND")
		(at 134.62 77.47 0)
		(unit 1)
		(exclude_from_sim no)
		(in_bom yes)
		(on_board yes)
		(dnp no)
		(uuid "00000000-0000-0000-0000-00005c26f707")
		(property "Reference" "#PWR06"
			(at 134.62 83.82 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Value" "GND"
			(at 134.62 81.28 0)
			(effects
				(font
					(size 1.27 1.27)
				)
			)
		)
		(property "Footprint" ""
			(at 134.62 77.47 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Datasheet" ""
			(at 134.62 77.47 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(property "Description" ""
			(at 134.62 77.47 0)
			(effects
				(font
					(size 1.27 1.27)
				)
				(hide yes)
			)
		)
		(pin "1"
			(uuid "6cc703cf-8089-4136-8dcb-0ac02e6fa39c")
		)
		(instances
			(project "AS5600 Breakout"
				(path "/8b2fb0b9-aa0a-43c0-9ebf-6130403d9509"
					(reference "#PWR06")
					(unit 1)
				)
			)
		)
	)
	(sheet_instances
		(path "/"
			(page "1")
		)
	)
)