meta.name = "Window test"
meta.version = "WIP"
meta.description = ""
meta.author = "Dregu"

local inputtext = ''
local inputnumber = 0
local inputslider = 6
local inputdrag = 9
local inputcombo = 1
local comboopts = { 'one', 'two', 'three' }
local inputcheck = false
local inputcolorrgb = Color:green()
local inputcolorrgba = Color:new(0.0, 0.0, 1.0, 0.5) -- 50% opacity blue

local inputtooltip = 'This input\'s value is used as its tooltip.'

local widgetopen = true
local closebutton = false

local tab_window_open = true
local custom_tab_bar_flags = GUI_TAB_BAR_FLAG.NONE
local next_custom_tab_id = 4
local custom_tabs = {
    {
        label = 'Tab 1',
        closeable = false,
        flags = GUI_TAB_ITEM_FLAG.LEADING
    },
    {
        label = 'Tab 2',
        closeable = false,
        flags = GUI_TAB_ITEM_FLAG.NONE
    },
    {
        label = 'Tab 3',
        closeable = true,
        flags = GUI_TAB_ITEM_FLAG.NONE
    }
}

local seedinput = ''
local seeddialogopen = false
local seeddialogclosebutton = false

-- load image to use later
local loadingimage = create_image('loading.png')

-- add a simple button to options to open our cluttered test windows
register_option_button('open', 'Open test window', function()
    widgetopen = true
end)
register_option_button('open2', 'Open tab window', function()
    tab_window_open = true
end)
register_option_button('open3', 'Open seed dialog', function()
    seeddialogopen = true
end)

-- draw a checkbox for a specific flag in a mask
local function draw_flag_checkbox(draw_ctx, label, flags, flag)
    if draw_ctx:win_check(label, test_mask(flags, flag)) then
        return set_mask(flags, flag)
    else
        return clr_mask(flags, flag)
    end
end

set_callback(function(draw_ctx)
    if closebutton then
        closebutton = false
        widgetopen = false
        message('Window was closed with a button')
    end
    if widgetopen then
        -- create a new window and test most of the widgets
        -- we'll put this one top center and make it movable, with no titlebar
        widgetopen = draw_ctx:window('##TestWindow', -0.3, 0.9, 0.6, 0.5, true, function(ctx, pos, size)
            draw_ctx:win_separator_text('Section One')

            draw_ctx:win_text(string.format("Geometry: %f,%f %f x %f", pos.x, pos.y, size.x, size.y))

            draw_ctx:win_width(0.12)
            draw_ctx:win_input_text('Width < 1.0 means the fraction of the window width', '')

            draw_ctx:win_width(-0.12)
            draw_ctx:win_input_text('I\'m short', 'Negative width means width of the description instead')

            draw_ctx:win_width(100)
            fixedwidth = draw_ctx:win_input_text('Fixed width textbox knows it only takes 12 characters', fixedwidth and fixedwidth:sub(0, 12) or '')

            -- open another window from this window
            if draw_ctx:win_button('Open seed dialog') then
                seeddialogopen = true
            end

            -- all the input widgets return the current value always, and expect you to keep feeding it back, or it will just revert to default when you blur the input
            local stupidexample = draw_ctx:win_input_text('Not like this', '') -- this will just always be empty

            -- you need to circulate your value through the widget like this
            inputtext = draw_ctx:win_input_text('Write text##texthereplease', inputtext)
            inputnumber = draw_ctx:win_input_int('Write number', inputnumber)
            inputslider = draw_ctx:win_slider_int('Select number##slider', inputslider, 1, 10)
            inputdrag = draw_ctx:win_drag_float('Select another number##drag', inputdrag, 1, 10)
            inputcombo = draw_ctx:win_combo('Combo thing', inputcombo, table.concat(comboopts, '\0')..'\0\0')
            inputcheck = draw_ctx:win_check('Check this out', inputcheck)
            inputcolorrgb = draw_ctx:win_color_editor('Color (RGB)', inputcolorrgb, false)
            inputcolorrgba = draw_ctx:win_color_editor('Color (RGBA)', inputcolorrgba, true)

            draw_ctx:win_separator_text('Section Two')
            -- pseudo table layout
            do
                -- four columns
                local n = 4
                local width = 1 / n
                local headers = {'Alpha', 'Beta', 'Gamma', 'Delta'}
                -- headers
                for i=1,n do
                    if i > 1 then draw_ctx:win_sameline(width*(i-1), 4) end
                    draw_ctx:win_text(headers[i])
                end
                -- textboxes with no label
                for i=1,n do
                    if i > 1 then draw_ctx:win_sameline(0, 4) end
                    draw_ctx:win_width(width)
                    whatever = draw_ctx:win_input_text(F'##BoxA{i}', whatever or '')
                end
                -- more textboxes with no label
                for i=1,n do
                    if i > 1 then draw_ctx:win_sameline(0, 4) end
                    draw_ctx:win_width(width)
                    whatever = draw_ctx:win_input_text(F'##BoxB{i}', whatever or '')
                end
            end
            draw_ctx:win_text('Click here:')
            draw_ctx:win_inline()
            if draw_ctx:win_button('Submit') then
                message(inputtext..' '..tostring(inputnumber)..' '..tostring(inputslider)..' '..tostring(inputdrag)..' '..comboopts[inputcombo]..' '..tostring(inputcheck)
                    ..' '..tostring(inputcolorrgb:get_ucolor())..' '..tostring(inputcolorrgba:get_ucolor()))
            end

            -- long text is wrapped
            draw_ctx:win_text('Sed non justo eu orci lacinia mollis. Morbi finibus luctus massa eu gravida. Maecenas ornare tincidunt pellentesque. Aliquam vel nulla eu mauris pulvinar consequat sed vitae nisi. Nulla facilisi. Nulla venenatis mollis mauris, sed blandit nisi auctor facilisis. In tempor magna eleifend, ornare sem in, egestas massa. Donec pulvinar orci ac ligula rhoncus, a hendrerit elit interdum. Maecenas sed orci quis justo imperdiet finibus.')

            -- add tooltips to widgets
            draw_ctx:win_text('Hover the cursor over this text to see a tooltip.')
            draw_ctx:win_tooltip('This is a tooltip for the text.')
            draw_ctx:win_button('This button has a tooltip too')
            draw_ctx:win_tooltip('This is a tooltip for the button.\nTooltips can have multiple lines.')
            inputtooltip = draw_ctx:win_input_text('Tooltip text input', inputtooltip)
            draw_ctx:win_tooltip(inputtooltip)

            -- draw the image we loaded before
            if loadingimage > -1 then
                draw_ctx:win_image(loadingimage, 0, 0)

                -- imagebutton, always 1/3 width of window, height smaller but keeps 3:1 aspect ratio
                draw_ctx:win_imagebutton('##coolbutton', loadingimage, 0.33, 0.11, 0, 0, 1, 1)
            end

            draw_ctx:win_separator_text('Identical Input Labels')

            -- remember to use unique labels on identical inputs
            if draw_ctx:win_button('Test##FirstTest') then
                message('First button')
            end
            if draw_ctx:win_button('Test##SecondTest') then
                message('Second button')
            end

            -- or distinguish between identical inputs with pushid (integer)
            a = {}
            for i=1,5 do
                draw_ctx:win_pushid(i)
                a[i] = draw_ctx:win_button('A')
                if i < 5 then
                    draw_ctx:win_inline()
                end
                draw_ctx:win_popid()
            end
            for i=1,5 do
                if a[i] then
                    message('Clicked A number '..tostring(i))
                end
            end

            -- or with pushid (string)
            local b_ids = { 'first', 'second', 'third' }
            b = {}
            for i, id in ipairs(b_ids) do
                draw_ctx:win_pushid(id)
                b[id] = draw_ctx:win_button('B')
                if i < #b_ids then
                    draw_ctx:win_inline()
                end
                draw_ctx:win_popid()
            end
            for _, id in ipairs(b_ids) do
                if b[id] then
                    message('Clicked B string '..id)
                end
            end

            closebutton = draw_ctx:win_button('Close window')

            -- circle the player, but only inside this window
            if #players > 0 then
                local x, y, l = get_position(players[1].uid)
                local sx, sy = screen_position(x, y)
                local radius = screen_distance(1) -- one tile
                draw_ctx:draw_layer(DRAW_LAYER.WINDOW)
                draw_ctx:draw_circle(sx, sy, radius, 3, rgba(255, 0, 0, 255))
                -- draw an inner circle using one of the colors from the window color editors
                draw_ctx:draw_circle(sx, sy, 0.75 * radius, 6, inputcolorrgba:get_ucolor())
            end

        end)
        if not widgetopen then
            message('Window was closed from the X')
        end
    end

    if tab_window_open then
        -- create a window showing tab examples
        -- position the window in the bottom-right quadrant of the screen
        tab_window_open = draw_ctx:window('Tab Examples', 0.2, 0.0, 0.7, 0.9, true, function()
            draw_ctx:win_tab_bar('MainTabBar', function()
                draw_ctx:win_tab_item('Small Tab', false, function()
                    draw_ctx:win_text('Not much to see here.')
                end)
                draw_ctx:win_tab_item('Large Tab', false, function()
                    draw_ctx:win_text('This tab has a lot of content.')
                    for i=1,30 do
                        draw_ctx:win_text('Content #'..i)
                        draw_ctx:win_inline()
                        draw_ctx:win_button('Button #'..i)
                    end
                end)
                draw_ctx:win_tab_item('Customization', false, function()
                    draw_ctx:win_text('Tab bar behavior can be customized. These are the settings for the tab bar below.')
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'Reorderable', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.REORDERABLE)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'Auto-select new tabs', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.AUTO_SELECT_NEW_TABS)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'Show tab list pop-up button', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.TAB_LIST_POPUP_BUTTON)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'No close with middle mouse button', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.NO_CLOSE_WITH_MIDDLE_MOUSE_BUTTON)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'No tab list scrolling buttons', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.NO_TAB_LIST_SCROLLING_BUTTONS)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'No tooltip when label is truncated', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.NO_TOOLTIP)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'Fitting policy: resize down', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.FITTING_POLICY_RESIZE_DOWN)
                    custom_tab_bar_flags = draw_flag_checkbox(draw_ctx, 'Fitting policy: scroll', custom_tab_bar_flags, GUI_TAB_BAR_FLAG.FITTING_POLICY_SCROLL)
                    local select_a_tab = false
                    if #custom_tabs > 0 then
                        if draw_ctx:win_button('Select '..custom_tabs[1].label) then
                            select_a_tab = true
                        end
                    end
                    draw_ctx:win_text('Use the "+" tab button to create more tabs.')
                    draw_ctx:win_tab_bar('CustomizedTabBar', custom_tab_bar_flags, function()
                        local i = 1
                        while i <= #custom_tabs do
                            local tab = custom_tabs[i]
                            local tab_flags = tab.flags
                            if i == 1 and select_a_tab then
                                -- enable the SET_SELECTED flag for one frame to force a tab to be selected
                                -- don't use this flag on every frame, or else it will be impossible to select any other tab
                                tab_flags = set_mask(tab_flags, GUI_TAB_ITEM_FLAG.SET_SELECTED)
                            end
                            local keep_tab = draw_ctx:win_tab_item(tab.label, tab.closeable, tab_flags, function()
                                -- all changes to these tab settings will be applied on the next frame that the tab is drawn
                                draw_ctx:win_text('Individual tab behavior can also be customized. These are the settings for '..tab.label..'.')
                                tab.closeable = draw_ctx:win_check('Closeable', tab.closeable)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'Show unsaved document indicator', tab.flags, GUI_TAB_ITEM_FLAG.UNSAVED_DOCUMENT)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'No close with middle mouse button', tab.flags, GUI_TAB_ITEM_FLAG.NO_CLOSE_WITH_MIDDLE_MOUSE_BUTTON)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'Don\'t push/pop tab ID around contents', tab.flags, GUI_TAB_ITEM_FLAG.NO_PUSH_ID)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'No tooltip when label is truncated', tab.flags, GUI_TAB_ITEM_FLAG.NO_TOOLTIP)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'No reordering', tab.flags, GUI_TAB_ITEM_FLAG.NO_REORDER)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'Leading', tab.flags, GUI_TAB_ITEM_FLAG.LEADING)
                                tab.flags = draw_flag_checkbox(draw_ctx, 'Trailing', tab.flags, GUI_TAB_ITEM_FLAG.TRAILING)
                            end)
                            if not keep_tab and test_mask(tab.flags, GUI_TAB_ITEM_FLAG.UNSAVED_DOCUMENT) then
                                -- the UNSAVED_DOCUMENT flag doesn't prevent tab closure
                                -- you need to skip closure yourself and add your own special behavior, such as showing a message or dialog
                                keep_tab = true
                                message('Prevented closure of '..tab.label..' with UNSAVED_DOCUMENT flag')
                            end
                            if keep_tab then
                                i = i + 1
                            else
                                table.remove(custom_tabs, i)
                            end
                        end
                        -- this button always appears at the end of the tab bar, even when the tabs are reorderable
                        if draw_ctx:win_tab_item_button('+', GUI_TAB_ITEM_FLAG.TRAILING) then
                            table.insert(custom_tabs, {
                                label = 'Tab '..next_custom_tab_id,
                                closeable = true,
                                flags = GUI_TAB_ITEM_FLAG.NONE
                            })
                            next_custom_tab_id = next_custom_tab_id + 1
                        end
                    end)
                end)
                if draw_ctx:win_tab_item_button('Button') then
                    message('Tab button pressed')
                end
            end)
        end)
    end

    -- another smaller thing opened from the larger thing
    if seeddialogclosebutton then
        seeddialogclosebutton = false
        seeddialogopen = false
    end
    if seeddialogopen then
        -- non movable prompt in the center of your screen
        seeddialogopen = draw_ctx:window('Enter seed', 0, 0, 0, 0, false, function()
            seedinput = draw_ctx:win_input_text('Seed', seedinput)
            local seed = tonumber(seedinput, 16)
            if draw_ctx:win_button('Set seed') and seed then
                seeddialogclosebutton = true
                set_seed(seed)
            end
        end)
    end
end, ON.GUIFRAME)
