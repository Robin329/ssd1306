/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ssd1306_advance.c
 * @brief     driver ssd1306 advance source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/30  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/10  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ssd1306_advance.h"

static ssd1306_handle_t gs_handle;        /**< ssd1306 handle */

/**
 * @brief     advance example init
 * @param[in] interface is the interface type
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ssd1306_advance_init(ssd1306_interface_t interface, ssd1306_address_t addr)
{
    volatile uint8_t res;
    
    /* link functions */
    DRIVER_SSD1306_LINK_INIT(&gs_handle, ssd1306_handle_t);
    DRIVER_SSD1306_LINK_IIC_INIT(&gs_handle, ssd1306_interface_iic_init);
    DRIVER_SSD1306_LINK_IIC_DEINIT(&gs_handle, ssd1306_interface_iic_deinit);
    DRIVER_SSD1306_LINK_IIC_WRITE(&gs_handle, ssd1306_interface_iic_write);
    DRIVER_SSD1306_LINK_SPI_INIT(&gs_handle, ssd1306_interface_spi_init);
    DRIVER_SSD1306_LINK_SPI_DEINIT(&gs_handle, ssd1306_interface_spi_deinit);
    DRIVER_SSD1306_LINK_SPI_WRITE_COMMAND(&gs_handle, ssd1306_interface_spi_write_cmd);
    DRIVER_SSD1306_LINK_SPI_COMMAND_DATA_GPIO_INIT(&gs_handle, ssd1306_interface_spi_cmd_data_gpio_init);
    DRIVER_SSD1306_LINK_SPI_COMMAND_DATA_GPIO_DEINIT(&gs_handle, ssd1306_interface_spi_cmd_data_gpio_deinit);
    DRIVER_SSD1306_LINK_SPI_COMMAND_DATA_GPIO_WRITE(&gs_handle, ssd1306_interface_spi_cmd_data_gpio_write);
    DRIVER_SSD1306_LINK_RESET_GPIO_INIT(&gs_handle, ssd1306_interface_reset_gpio_init);
    DRIVER_SSD1306_LINK_RESET_GPIO_DEINIT(&gs_handle, ssd1306_interface_reset_gpio_deinit);
    DRIVER_SSD1306_LINK_RESET_GPIO_WRITE(&gs_handle, ssd1306_interface_reset_gpio_write);
    DRIVER_SSD1306_LINK_DELAY_MS(&gs_handle, ssd1306_interface_delay_ms);
    DRIVER_SSD1306_LINK_DEBUG_PRINT(&gs_handle, ssd1306_interface_debug_print);
    
    /* set interface */
    res = ssd1306_set_interface(&gs_handle, interface);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set interface failed.\n");
        
        return 1;
    }
    
    /* set addr pin */
    res = ssd1306_set_addr_pin(&gs_handle, addr);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set addr failed.\n");
        
        return 1;
    }
    
    /* ssd1306 init */
    res = ssd1306_init(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: init failed.\n");
        
        return 1;
    }
    
    /* close display */
    res = ssd1306_set_display(&gs_handle, SSD1306_DISPLAY_OFF);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set column address range */
    res = ssd1306_set_column_address_range(&gs_handle, SSD1306_ADVANCE_DEFAULT_COLUMN_ADDRESS_RANGE_START, SSD1306_ADVANCE_DEFAULT_COLUMN_ADDRESS_RANGE_END);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set column address range failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set page address range */
    res = ssd1306_set_page_address_range(&gs_handle, SSD1306_ADVANCE_DEFAULT_PAGE_ADDRESS_RANGE_START, SSD1306_ADVANCE_DEFAULT_PAGE_ADDRESS_RANGE_END);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set page address range failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set low column start address */
    res = ssd1306_set_low_column_start_address(&gs_handle, SSD1306_ADVANCE_DEFAULT_LOW_COLUMN_START_ADDRESS);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set low column start address failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set high column start address */
    res = ssd1306_set_high_column_start_address(&gs_handle, SSD1306_ADVANCE_DEFAULT_HIGH_COLUMN_START_ADDRESS);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set high column start address failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display start line */
    res = ssd1306_set_display_start_line(&gs_handle, SSD1306_ADVANCE_DEFAULT_DISPLAY_START_LINE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display start line failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set fade blinking mode */
    res = ssd1306_set_fade_blinking_mode(&gs_handle, SSD1306_ADVANCE_DEFAULT_FADE_BLINKING_MODE, SSD1306_ADVANCE_DEFAULT_FADE_FRAMES);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set fade blinking failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* deactivate scroll */
    res = ssd1306_deactivate_scroll(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set deactivate scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set zoom in */
    res = ssd1306_set_zoom_in(&gs_handle, SSD1306_ADVANCE_DEFAULT_ZOOM_IN);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set set zoom in failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set contrast */
    res = ssd1306_set_contrast(&gs_handle, SSD1306_ADVANCE_DEFAULT_CONTRAST);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set contrast failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set segment remap */
    res = ssd1306_set_segment_remap(&gs_handle, SSD1306_ADVANCE_DEFAULT_SEGMENT);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set segment remap failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set scan direction */
    res = ssd1306_set_scan_direction(&gs_handle, SSD1306_ADVANCE_DEFAULT_SCAN_DIRECTION);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set scan direction failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display mode */
    res = ssd1306_set_display_mode(&gs_handle, SSD1306_ADVANCE_DEFAULT_DISPLAY_MODE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display mode failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set multiplex ratio */
    res = ssd1306_set_multiplex_ratio(&gs_handle, SSD1306_ADVANCE_DEFAULT_MULTIPLEX_RATIO);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set multiplex ratio failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display offset */
    res = ssd1306_set_display_offset(&gs_handle, SSD1306_ADVANCE_DEFAULT_DISPLAY_OFFSET);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display offset failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display clock */
    res = ssd1306_set_display_clock(&gs_handle, SSD1306_ADVANCE_DEFAULT_OSCILLATOR_FREQUENCY, SSD1306_ADVANCE_DEFAULT_CLOCK_DIVIDE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display clock failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set precharge period */
    res = ssd1306_set_precharge_period(&gs_handle, SSD1306_ADVANCE_DEFAULT_PHASE1_PERIOD, SSD1306_ADVANCE_DEFAULT_PHASE2_PERIOD);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set pre charge period failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set hardware pins conf */
    res = ssd1306_set_com_pins_hardware_conf(&gs_handle, SSD1306_ADVANCE_DEFAULT_PIN_CONF, SSD1306_ADVANCE_DEFAULT_LEFT_RIGHT_REMAP);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set com pins hardware conf failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set deselect level 0.77 */
    res = ssd1306_set_deselect_level(&gs_handle, SSD1306_ADVANCE_DEFAULT_DESELECT_LEVEL);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set deselect level failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set page memory addressing mode */
    res = ssd1306_set_memory_addressing_mode(&gs_handle, SSD1306_MEMORY_ADDRESSING_MODE_PAGE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set memory addressing level failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable charge pump */
    res = ssd1306_set_charge_pump(&gs_handle, SSD1306_CHARGE_PUMP_ENABLE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set charge pump failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* entire display off */
    res = ssd1306_set_entire_display(&gs_handle, SSD1306_ENTIRE_DISPLAY_OFF);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set entire display failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable display */
    res = ssd1306_set_display(&gs_handle, SSD1306_DISPLAY_ON);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear screen */
    res = ssd1306_clear(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: clear failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  advance example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ssd1306_advance_deinit(void)
{
    /* deinit ssd1306 */
    if (ssd1306_deinit(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  advance example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t ssd1306_advance_display_on(void)
{
    volatile uint8_t res;
    
    /* display on */
    res = ssd1306_set_display(&gs_handle, SSD1306_DISPLAY_ON);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display failed.\n");
        
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  advance example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t ssd1306_advance_display_off(void)
{
    volatile uint8_t res;
    
    /* display off */
    res = ssd1306_set_display(&gs_handle, SSD1306_DISPLAY_OFF);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set display failed.\n");
        
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  advance example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t ssd1306_advance_clear(void)
{
    /* clear */
    if (ssd1306_clear(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     advance example write a point
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] data is the written data
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 * @note      none
 */
uint8_t ssd1306_advance_write_point(uint8_t x, uint8_t y, uint8_t data)
{
    volatile uint8_t res;
    
    /* write point */
    res = ssd1306_write_point(&gs_handle, x, y, data);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: write point failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief      advance example read a point
 * @param[in]  x is the coordinate x
 * @param[in]  y is the coordinate y
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read point failed
 * @note       none
 */
uint8_t ssd1306_advance_read_point(uint8_t x, uint8_t y, uint8_t *data)
{
    volatile uint8_t res;
    
    /* read point in gram */
    res = ssd1306_read_point(&gs_handle, x, y, data);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: read point failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief     advance example draw a string
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] *str points to a written string address
 * @param[in] len is the length of the string
 * @param[in] color is the display color
 * @param[in] font is the display font size
 * @return    status code
 *            - 0 success
 *            - 1 write string failed
 * @note      none
 */
uint8_t ssd1306_advance_string(uint8_t x, uint8_t y, char *str, uint16_t len, uint8_t color, ssd1306_font_t font)
{
    volatile uint8_t res;
    
    /* write stirng in gram */
    res = ssd1306_gram_write_string(&gs_handle, x, y, str, len, color, font);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: gram write string failed.\n");
       
        return 1;
    }
    
    /* update gram */
    if (ssd1306_gram_update(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     advance example fill a rectangle
 * @param[in] left is the left coordinate x
 * @param[in] top is the left coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the right coordinate y
 * @param[in] color is the display color
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 * @note      none
 */
uint8_t ssd1306_advance_rect(int8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color)
{
    volatile uint8_t res;
    
    /* fill rect in gram */
    res = ssd1306_gram_fill_rect(&gs_handle, left, top, right, bottom, color);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: gram fill rect failed.\n");
       
        return 1;
    }
    
    /* update gram */
    if (ssd1306_gram_update(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     advance example draw a picture
 * @param[in] left is the left coordinate x
 * @param[in] top is the left coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the right coordinate y
 * @param[in] *img points to a image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture failed
 * @note      none
 */
uint8_t ssd1306_advance_picture(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img)
{
    volatile uint8_t res;
    
    /* draw picture in gram */
    res = ssd1306_gram_draw_picture(&gs_handle, left, top, right, bottom, img);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: gram draw picture failed.\n");
        
        return 1;
    }
    
    /* update gram */
    if (ssd1306_gram_update(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  advance example enable the zoom in
 * @return status code
 *         - 0 success
 *         - 1 enable zoom in failed
 * @note   none
 */
uint8_t ssd1306_advance_enable_zoom_in(void)
{
    volatile uint8_t res;
    
    /* enable zoom in */
    res = ssd1306_set_zoom_in(&gs_handle, SSD1306_ZOOM_IN_ENABLE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set set zoom in failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  advance example disable the zoom in
 * @return status code
 *         - 0 success
 *         - 1 disable zoom in failed
 * @note   none
 */
uint8_t ssd1306_advance_disable_zoom_in(void)
{
    volatile uint8_t res;
    
    /* disable zoom in */
    res = ssd1306_set_zoom_in(&gs_handle, SSD1306_ZOOM_IN_DISABLE);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set set zoom in failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief     advance example set the fade blinking mode
 * @param[in] mode is the fade blinking mode
 * @param[in] frames is the fade or blinking frames
 * @return    status code
 *            - 0 success
 *            - 1 set fade blinking mode failed
 * @note      frames max is 0x0F and div is (frames + 1) * 8
 */
uint8_t ssd1306_advance_fade_blinking(ssd1306_fade_blinking_mode_t mode, uint8_t frames)
{
    volatile uint8_t res;
    
    /* set fade blinking mode */
    res = ssd1306_set_fade_blinking_mode(&gs_handle, mode, frames);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: setf fade blinking failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  advance example deactivate the scroll
 * @return status code
 *         - 0 success
 *         - 1 deactivate scroll failed
 * @note   none
 */
uint8_t ssd1306_advance_deactivate_scroll(void)
{
    volatile uint8_t res;
    
    /* deactivate scroll */
    res = ssd1306_deactivate_scroll(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set deactivate scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief     advance example enable the left horizontal scroll
 * @param[in] start_page_addr is the start page address
 * @param[in] end_page_addr is the end page address
 * @param[in] rows is the row address
 * @param[in] frames is the scroll frames
 * @return    status code
 *            - 0 success
 *            - 1 enable left horizontal scroll failed
 * @note      start_page_addr <= 0x07, end_page_addr <= 0x07, rows <= 0x3F
 */
uint8_t ssd1306_advance_vertical_left_horizontal_scroll(uint8_t start_page_addr, uint8_t end_page_addr, uint8_t rows, 
                                                        ssd1306_scroll_frame_t frames)
{
    volatile uint8_t res;
    
    /* deactivate scroll */
    res = ssd1306_deactivate_scroll(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set deactivate scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    /* set vertical left horizontal scroll */
    res = ssd1306_set_vertical_left_horizontal_scroll(&gs_handle, start_page_addr, end_page_addr, rows, frames);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set vertical left horizontal scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    /* ativate scroll */
    res = ssd1306_ativate_scroll(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: ativate scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief     advance example enable the right horizontal scroll
 * @param[in] start_page_addr is the start page address
 * @param[in] end_page_addr is the end page address
 * @param[in] rows is the row address
 * @param[in] frames is the scroll frames
 * @return    status code
 *            - 0 success
 *            - 1 enable right horizontal scroll failed
 * @note      start_page_addr <= 0x07, end_page_addr <= 0x07, rows <= 0x3F
 */
uint8_t ssd1306_advance_vertical_right_horizontal_scroll(uint8_t start_page_addr, uint8_t end_page_addr, uint8_t rows, 
                                                         ssd1306_scroll_frame_t frames)
{
    volatile uint8_t res;
    
    /* deactivate scroll */
    res = ssd1306_deactivate_scroll(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set deactivate scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    /* set vertical right horizontal scroll */
    res = ssd1306_set_vertical_right_horizontal_scroll(&gs_handle, start_page_addr, end_page_addr, rows, frames);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: set vertical right horizontal scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    /* ativate scroll */
    res = ssd1306_ativate_scroll(&gs_handle);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: ativate scroll failed.\n");
        ssd1306_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}
